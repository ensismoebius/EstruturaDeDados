#include <stdio.h>
#include <stdlib.h>

#include "lib/linkedList"
#include "lib/strFuncs.h"

double applyOperation(char operation, double firstNumber, double secondNumber) {

	double result = 0;

	switch (operation) {
	case '+':
		result = firstNumber + secondNumber;
		break;
	case '-':
		result = firstNumber - secondNumber;
		break;
	case '*':
		result = firstNumber * secondNumber;
		break;
	case '/':
		if (secondNumber == 0) {
			return NULL;
		}
		result = firstNumber / secondNumber;
	}
	return result;
}

char isPartOfANumber(char c) {
	if (c >= '0' && c <= '9') {
		return 1;
	}
	if (c == '.') {
		return 1;
	}
	return 0;
}

float evaluateExpression(char* tokens, int length) {

	trim(tokens);

	list values;
	list ops;

	for (int i = 0; i < length; ++i) {

		if (tokens[i] == ' ')
			continue;

		if (tokens[i] >= '0' && tokens[i] <= '9') {

			// There may be more than one digits in number
			int numberIndex = 0;
			char number[255];

			while (i < length && isPartOfANumber(tokens[i])) {
				number[numberIndex++] = tokens[i];
			}

			// Closing the string that represents the number
			number[numberIndex] = '\0';

			// After number has been built push it into the numbers stack
			push(values, strtod(number));

			// We must subtract 1 at the index because the next
			// interaction will add 1, doing this we can keep track
			// of the tokens
			i--;

			// After build the number goto to next char/iteration
			continue;
		}

		// Current token is an opening brace, push it to 'ops'
		if (tokens[i] == '(') {
			push(ops, tokens[i]);
			continue;
		}

		// Closing brace encountered, solve entire brace
		if (tokens[i] == ')') {
			while (peek(ops) != '(') {
				push(values, applyOperation(pop(ops), pop(values), pop(values)));
			}
			pop(ops);
			continue;
		}

		// Current token is an operator.
		if (tokens[i] == '+' || tokens[i] == '-' || tokens[i] == '*' || tokens[i] == '/' || tokens[i] == '=') {
			// While top of 'ops' has same or greater precedence to current
			// token, which is an operator. Apply operator on top of 'ops'
			// to top two elements in values stack
			while (!empty(ops) && hasPrecedence(tokens[i], peek(ops))) {
				push(values, applyOperation(pop(ops), pop(values), pop(values)));
			}

			// Push current token to 'ops'.
			push(ops, tokens[i]);
		}
	}

	// Entire expression has been parsed at this point, apply remaining
	// ops to remaining values
	while (!empty(ops)) {
		push(values, applyOperation(pop(ops), pop(values), pop(values)));
	}

	// Top of 'values' contains result, return it
	return pop(values)->value;
}

int main(int argc, char **argv) {

	char texto[] = "1+2";

	float result = evaluateExpression(texto);

	printf("%f", result);
	gets();
//	trim(texto);
//	puts(texto);

//	list* list2 = createList();
//	list* list1 = createList();
//	list* list3 = createList();
//
//	addNextItem(list1, 10.0);
//	addNextItem(list1, 11.0);
//	addNextItem(list1, 12.0);
//	addNextItem(list1, 13.0);
//	addNextItem(list1, 14.0);
//	addAfter(list1, -1, 9.0);
//	addNextItem(list1, 16.0);
//	addNextItem(list1, 17.0);
//	addAfter(list1, 5, 15.0);
//
//	addNextItem(list2, 0.0);
//	addNextItem(list2, 1.0);
//	addNextItem(list2, 2.0);
//	addNextItem(list2, 3.0);
//	addNextItem(list2, 4.0);
//	addNextItem(list2, 5.0);
//	addNextItem(list2, 6.0);
//	addNextItem(list2, 7.0);
//	addNextItem(list2, 8.0);
//
//	joinLists(list2, list1);
//	listItem* k = findOneByValue(list, 12.0);
//	deleteByIndex(list, 1);
//	swapItems(list, 3, 0);

//	showAll(list1);

//	push(list3, 100.0);
//	push(list3, 101.0);
//	push(list3, 102.0);
//	push(list3, 103.0);
//	push(list3, 104.0);
//	push(list3, 105.0);
//
//	pop(list3);
//	pop(list3);
//	pop(list3);
//
//	showAll(list3);
//
//	clearList(list3);
//
//	showAll(list3);
	return 0;
}
