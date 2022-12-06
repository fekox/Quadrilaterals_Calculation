#include "raylib.h"
#include "Loop.h"
#include <cmath>

using namespace std;

int area;//Variable para guardar el area.

int surface;//Variable para guardar la superficie.

//Variables del Struct para las lineas
Line line1;
Line line2;
Line line3;
Line line4;

int main()
{
	//Coordenadas iniciales para las lineas (Aparecen fuera de la pantalla).
	line1.startPos.x = -100;
	line1.startPos.y = -100;
	line1.endPos.x = -400;
	line1.endPos.y = -400;
	
	line2.startPos.x = -7000;
	line2.startPos.y = -7000;
	line2.endPos.x = -7500;
	line2.endPos.y = -7500;
	
	line3.startPos.x = 2000;
	line3.startPos.y = 2000;
	line3.endPos.x = 2000;
	line3.endPos.y = 2000;
	
	line4.startPos.x = 3000;
	line4.startPos.y = 3000;
	line4.endPos.x = 3000;
	line4.endPos.y = 3000;
	
	//Inicio los limites de la pantalla
	InitWindow(1920, 1080, "Algebra_TP1");
	SetWindowState(FLAG_VSYNC_HINT);

	//Loop de programa
	while (!WindowShouldClose())
	{ 
		//Variable local utilizada para saber cuando se cambia de linea.
		static int numberOfChange = 0;

		//Comienzo a dibujar la pantalla.
		BeginDrawing();
		ClearBackground(BLACK);

		//Funcion para chequear si las lineas estan colisionando.
		ChecLinesCollision();

		//Si se toca la Barra Espaciadora se cambia la variable y asi se sabe que linea se dibuja.
		if (IsKeyPressed(KEY_SPACE))
		{
			numberOfChange += 1;
			if (numberOfChange > 3)
			{
				numberOfChange = 0;
			}
		}

		//Chequeo en que linea se encuentra y llamo a la funcion para dibujarla y cambiar su posicion.
		if (numberOfChange == 0)
		{
			selectionLine(line1);
		}

		if (numberOfChange == 1)
		{
			selectionLine(line2);
		}

		if (numberOfChange == 2)
		{
			selectionLine(line3);
		}

		if (numberOfChange == 3)
		{
			selectionLine(line4);
		}

		//Imprimo instrucciones
		DrawText(TextFormat("Tocar 'Espacio' para cambiar de linea"), 50, 10, 40, PURPLE);
		DrawText(TextFormat("Tocar 'Click Izquierdo' para cambiar inicio de la linea"), 50, 50, 40, PURPLE);
		DrawText(TextFormat("Tocar 'Click Derecho' para cambiar final de la linea"), 50, 90, 40, PURPLE);

		//Se diibujan las lineas durante el loop para que no desaparezcan y aparezcan de la nada
		DrawLineEx(line1.startPos, line1.endPos, line1.width, WHITE);
		DrawLineEx(line2.startPos, line2.endPos, line2.width, WHITE);
		DrawLineEx(line3.startPos, line3.endPos, line3.width, WHITE);
		DrawLineEx(line4.startPos, line4.endPos, line4.width, WHITE);

		//Finalizo el dibujado de la pantalla
		EndDrawing();
	}

	//Cierro la ejecucion si sale del loop
	CloseWindow();

	return 0;
}

//Funcion que recibe que linea es la que se quiere dibujar y cambiar de posicion
void selectionLine(Line& actualLine)
{
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) actualLine.startPos = GetMousePosition();
	else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) actualLine.endPos = GetMousePosition();

	DrawLineEx(actualLine.startPos, actualLine.endPos, actualLine.width, WHITE);
}

//Funcion para chequear si las lineas estan colisionando.
void ChecLinesCollision()
{
	//Collsiones de la primera linea.

	if(CheckCollisionLines(line1.startPos, line1.endPos, line2.startPos, line2.endPos, line1.collisionPoint))
	{
		line1.isCollision = true;
	}

	if (CheckCollisionLines(line1.startPos, line1.endPos, line3.startPos, line3.endPos, line1.collisionPoint))
	{
		line1.isCollision = true;
	}

	if (CheckCollisionLines(line1.startPos, line1.endPos, line4.startPos, line4.endPos, line1.collisionPoint))
	{
		line1.isCollision = true;
	}

	//Collsiones de la segunda linea.

	if (CheckCollisionLines(line2.startPos, line2.endPos, line1.startPos, line1.endPos, line1.collisionPoint))
	{
		line2.isCollision = true;
	}

	if (CheckCollisionLines(line2.startPos, line2.endPos, line3.startPos, line3.endPos, line1.collisionPoint))
	{
		line2.isCollision = true;
	}

	if (CheckCollisionLines(line2.startPos, line2.endPos, line4.startPos, line4.endPos, line1.collisionPoint))
	{
		line2.isCollision = true;
	}

	//Collsiones de la segunda linea.

	if (CheckCollisionLines(line3.startPos, line3.endPos, line1.startPos, line1.endPos, line1.collisionPoint))
	{
		line3.isCollision = true;
	}

	if (CheckCollisionLines(line3.startPos, line3.endPos, line2.startPos, line2.endPos, line1.collisionPoint))
	{
		line3.isCollision = true;
	}

	if (CheckCollisionLines(line3.startPos, line3.endPos, line4.startPos, line4.endPos, line1.collisionPoint))
	{
		line3.isCollision = true;
	}

	//Collsiones de la cuarta linea.

	if (CheckCollisionLines(line4.startPos, line4.endPos, line1.startPos, line1.endPos, line1.collisionPoint))
	{
		line4.isCollision = true;
	}

	if (CheckCollisionLines(line4.startPos, line4.endPos, line2.startPos, line2.endPos, line1.collisionPoint))
	{
		line4.isCollision = true;
	}

	if (CheckCollisionLines(line4.startPos, line4.endPos, line3.startPos, line3.endPos, line1.collisionPoint))
	{
		line4.isCollision = true;
	}
	
	else
	{
		line4.isCollision = false;
		line1.isCollision = false;
		line2.isCollision = false;
		line3.isCollision = false;
	}


	//Si todas las lineas colicionan, se realiza el calculo del area y la superficie. 
	if (line1.isCollision == true && line2.isCollision == true && line3.isCollision == true && line4.isCollision == true)
	{
		line1.length = GetLength(line1.startPos.x, line1.startPos.y, line1.endPos.x, line1.endPos.y);

		line2.length = GetLength(line2.startPos.x, line2.startPos.y, line2.endPos.x, line2.endPos.y);

		area = line1.length * line2.length;

		surface = line2.length;

		DrawText(TextFormat("Area = %03i", area), GetScreenWidth() / 3, GetScreenHeight() / 4, 40, PURPLE);
		DrawText(TextFormat("Superficie = %03i", surface), GetScreenWidth() / 1.5, GetScreenHeight() / 4, 40, PURPLE);
	}
}

//Funcion que devuelve el largo de una linea (Teorema de Pitagoras).
int GetLength(int point1X, int point1Y, int point2X, int point2Y)
{
	return sqrt(pow(point1X - point1Y, 2) + pow(point2X - point2Y, 2));
}