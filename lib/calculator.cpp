#include <stdlib.h>

#include "linkedList.h"
#include "strFuncs.h"
#include "stack.h"

listItem *applyOperation(listItem *operation, listItem *firstNumber, listItem *secondNumber) {

	double result = 0;

	char op = (char) *operation->value;
	double fn = *firstNumber->value;
	double sn = *secondNumber->value;

	free(operation);
	free(firstNumber);
	free(secondNumber);

	switch (op) {
		case '+':
			result = fn + sn;
			break;
		case '-':
			result = fn - sn;
			break;
		case '*':
			result = fn * sn;
			break;
		case '/':
			if (sn == 0) {
				exit(1);
			}
			result = fn / sn;
	}
	return createItem(result);
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

char hasPrecedence(char op1, char op2) {
	if (op2 == '=') return 0;

	if (op2 == '(' || op2 == ')') return 0;
	if ((op1 == '*' || op1 == '/') && (op2 == '+' || op2 == '-')) return 0;
	else return 1;
}

float evaluateExpression(char* tokens, int length) {

	trim(tokens);

	list* values = createList();
	list* ops = createList();

	for (int i = 0; i < length; ++i) {

		if (tokens[i] == ' ') continue;

		if (tokens[i] >= '0' && tokens[i] <= '9') {

			// There may be more than one digits in number
			int numberIndex = 0;
			char number[255];

			while (i < length && isPartOfANumber(tokens[i])) {
				number[numberIndex++] = tokens[i++];
			}

			// Closing the string that represents the number
			number[numberIndex] = '\0';

			// After number has been built push it into the numbers stack
			push(values, createItem(atof(number)));

			// We must subtract 1 at the index because the next
			// interaction will add 1, doing this we can keep track
			// of the tokens
			i--;

			// After build the number goto to next char/iteration
			continue;
		}

		// Current token is an opening brace, push it to 'ops'
		if (tokens[i] == '(') {
			push(ops, createItem(tokens[i]));
			continue;
		}

		// Closing brace encountered, solve entire brace
		if (tokens[i] == ')') {

			while (((char) *(peek(ops)->value)) != '(') {
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
			while (!empty(ops) && hasPrecedence(tokens[i], *(peek(ops)->value))) {
				push(values, applyOperation(pop(ops), pop(values), pop(values)));
			}

			// Push current token to 'ops'.
			push(ops, createItem(tokens[i]));
		}
	}

	// Entire expression has been parsed at this point, apply remaining
	// ops to remaining values
	while (!empty(ops)) {
		push(values, applyOperation(pop(ops), pop(values), pop(values)));
	}

	// Top of 'values' contains result, return it
	return *(pop(values)->value);
}
