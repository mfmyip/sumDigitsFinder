// 42 = 6

let init = 1;
let final = -1;

let expected = 1;

function setup() {
	//findNextLargest(init, result);
	createCanvas(windowWidth, windowHeight);
	//findNextLargest(init);
}

let newRes = -1;	
function draw() {
	background(0);
	fill(255);
	if (newRes <= init) {
		newRes = findNextLargest(init);
	}
	textSize(windowHeight/5 * 0.2);
	text("\""+init+"\"",windowWidth * 0.1, windowHeight/2 - windowHeight/5);
	textSize(windowHeight/5);
	text("\""+newRes+"\"\u2192"+expected,windowWidth * 0.1, windowHeight/2);
}

function findNextLargest(n) {
	let digits = reverse(Array.from(String(n), Number)); // [4, 2]
	let res = sum_arr(digits);
	print(res);
	let i = 1; // start from index at 1 to compare with the 0th digit, 
			   //no need to compare the 0th digit as increasing it would change the value of the sum
	// unless we only have 1 element
	if (digits.length === 1) {
		i = 0;
	}
	while(i > 0) {
		// finds the index at which we do our operation
		if (digits[i] < digits[i - 1]) {
			break;
		} else if (digits[i] === digits[i - 1]) {
			if (0 < digits[i] && digits[i] < 9) {
				break;
			}
		}
		if (i === digits.length - 1) { // base case
			break;
		}
		i++;
	}
	print("index:", i)
	if (digits[i] < 9 && digits[i] < res) { 
		// if our i-th digit is less than 9, simply adding 1, 
		// then finding the smallest max (for indices 0 to (i-1)) will yield the result
		digits[i]++;
		let comp = res - sum_arr(digits, i, digits.length - 1);
		print("comp:", comp);
		let tempArr = find_smallest(comp, i); // gets the array w the number we need to insert
		print(concat_digits(tempArr));
		for (let j = 0; j < tempArr.length; j++) {
			digits[j] = tempArr[j];
		}
	} else { // the value is 9, then we need to add a new digit
		digits.push(1);
		let comp = res - 1;
		print("comp:", comp);
		let tempArr = find_smallest(comp, i + 1); // gets the array w the number we need to insert
		for (let j = 0; j < tempArr.length; j++) {
			digits[j] = tempArr[j];
		}
	}
	final = concat_digits(digits);
	print("result:",final);

	// check correctness
	if (sum_arr(digits) != res) {
		print("ERROR");
	}
	return final;
}

function keyPressed() {
	if (key === 'i') {
		init = findNextLargest(final);
	}
}


// sums all the elements in arr, given range:
// min = mininum starting index
// max = ending index
function sum_arr(arr, min = 0, max = -1) {
	if (max === -1) {
		max = arr.length - 1;
	}

	let ret = 0;
	for (let i = min; i <= max; i++) {
		ret += arr[i];
	}
	return ret;
}

// given an array length n, finds the smallest possible n-digit number satisfying
// that the digits add up to input x. 
// Once found, constructs and returns an array of that number.
function find_smallest(x, arrLen) {
	let ret = [];
	for (let i = 0; i < arrLen; i++) {
		if (x > 9) { // 9 because highest digit
			ret[i] = 9;
			x -= 9;
		} else {
			ret[i] = max(0, x);
			x -= 9;
		}
	}
	return ret;
}

function concat_digits(arr) {
	let ret = 0;
	for (let i = 0; i < arr.length; i++) {
		ret = ret + arr[i]*Math.pow(10, i);
	}
	return ret;
}