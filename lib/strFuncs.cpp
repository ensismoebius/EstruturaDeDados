/**
 * Trim all the excess spaces in the string
 */
void trim(char* text) {

	unsigned char spaceCounter = 0;

	unsigned int counter = 0;
	unsigned int resultIndex = 0;

	while (text[counter] == ' ')
		counter++;

	text[resultIndex] = text[counter];

	while (text[counter] != '\0') {

		if (spaceCounter > 0) {
			while (text[counter] == ' ')
				counter++;

			spaceCounter = 0;
			continue;
		}

		if (text[counter] == ' ') {
			text[resultIndex] = text[counter];
			spaceCounter++;
			resultIndex++;
			counter++;
			continue;
		}

		text[resultIndex] = text[counter];
		spaceCounter = 0;
		resultIndex++;
		counter++;
	}

	if (text[resultIndex - 1] == ' ') {
		text[resultIndex - 1] = '\0';
		return;
	}

	text[resultIndex] = '\0';
}
