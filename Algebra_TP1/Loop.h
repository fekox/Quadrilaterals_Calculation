#pragma once

//Struct de lo que contienen las lineas
struct Line
{
	Vector2 startPos;
	Vector2 endPos;

	Vector2* collisionPoint;

	bool isCollision;

	float width = 10;

	int length;
};

int GetLength(int point1X, int point1Y, int point2X, int point2Y);

void ChecLinesCollision();

void selectionLine(Line& actualLine);