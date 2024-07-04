#pragma once
int relu(int torelu) {
	if (0 > torelu) return 0;
	return torelu;
}

double relu(double torelu) {
	if (0 > torelu) return 0;
	return torelu;
}

float relu(float torelu) {
	if (0 > torelu) return 0;
	return torelu;
}