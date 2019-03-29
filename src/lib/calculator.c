/*
 * calculator.c
 *
 *  Created on: 27 de mar de 2019
 *      Author: ensis
 */

#include <stdio.h>

char *evaluate(char expression[]) {

	return 1;
}
//
//		// Ignores empty expressions
//		if (expression.trim().isEmpty()) {
//			return "";
//		}
//
//		// An array of tokens
//		char[] tokens = expression.toCharArray();
//
//		// Stack for numbers: 'values'
//		Stack<String> values = new Stack<String>();
//
//		// Stack for Operators: 'ops'
//		Stack<Character> ops = new Stack<Character>();
//
//		// Cicles over all tokens in expression
//		for (int i = 0; i < tokens.length; i++) {
//			// Current token is a whitespace, skip it
//			if (tokens[i] == ' ') {
//				continue;
//			}
//
//			// Current token is a number, push it to stack for numbers
//			if (tokens[i] >= '0' && tokens[i] <= '9' || Character.isAlphabetic(tokens[i])) {
//
//				// There may be more than one digits in number
//				StringBuffer sbuf = new StringBuffer();
//				while (i < tokens.length && (isPartOfANumber(tokens[i]) || isPartOfAVariable(tokens[i]))) {
//					sbuf.append(tokens[i++]);
//				}
//
//				// After number has been built push it into the numbers stack
//				values.push(sbuf.toString());
//
//				// We must subtract 1 at the index because the next
//				// interaction will add 1, doing this we can keep track
//				// of the tokens
//				i--;
//
//				// After build the number goto to next char/iteration
//				continue;
//			}
//
//			// Current token is an opening brace, push it to 'ops'
//			if (tokens[i] == '(') {
//				ops.push(tokens[i]);
//				continue;
//			}
//
//			// Closing brace encountered, solve entire brace
//			if (tokens[i] == ')') {
//				while (ops.peek() != '(') {
//					values.push(applyOperation(ops.pop(), values.pop(), values.pop()));
//				}
//				ops.pop();
//				continue;
//			}
//
//			// Current token is an operator.
//			if (tokens[i] == '+' || tokens[i] == '-' || tokens[i] == '*' || tokens[i] == '/' || tokens[i] == '=') {
//				// While top of 'ops' has same or greater precedence to current
//				// token, which is an operator. Apply operator on top of 'ops'
//				// to top two elements in values stack
//				while (!ops.empty() && hasPrecedence(tokens[i], ops.peek())) {
//					values.push(applyOperation(ops.pop(), values.pop(), values.pop()));
//				}
//
//				// Push current token to 'ops'.
//				ops.push(tokens[i]);
//			}
//		}
//
//		// Entire expression has been parsed at this point, apply remaining
//		// ops to remaining values
//		while (!ops.empty()) {
//			values.push(applyOperation(ops.pop(), values.pop(), values.pop()));
//		}
//
//		// Top of 'values' contains result, return it
//		return values.pop();
//	}
//
//
