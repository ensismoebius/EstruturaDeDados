/*
 * calculator.h
 *
 *  Created on: 4 de abr de 2019
 *      Author: ensis
 */

#ifndef LIB_CALCULATOR_H_
#define LIB_CALCULATOR_H_

char isPartOfANumber(char c);
char hasPrecedence(char op1, char op2);
float evaluateExpression(char* tokens, int length);
listItem *applyOperation(listItem *operation, listItem *firstNumber, listItem *secondNumber);

#endif /* LIB_CALCULATOR_H_ */
