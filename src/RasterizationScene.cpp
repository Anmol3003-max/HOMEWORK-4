#include "RasterizationScene.h"
#include "Rasterization.h"
#include "ImageUtils.h"
#include "Camera.h"
#include "Time.h"

float sdCircle(Vector2 p, float r);
float step(float edge, float x);

void Example1();
void Example2();

void RasterizationScene::OnLoad()
{
}

void RasterizationScene::OnUnload()
{
}

void RasterizationScene::OnUpdate(float dt)
{
	ClearColor(&gImageCPU, BLACK);
	//Example1();
	//Example2();

	// Example function call from Rasterization.h
	// Should render a horizontal line around the bottom-right quadrant of your screen!
	DrawLineX(&gImageCPU, 100, 200, 400, RED);

	// Homework:
	// Draw a border around your screen using DrawRectLines
	// Draw a border around your screen using DrawRectLines
	// Draw a border around your screen using DrawRectLines
	DrawRectLines(&gImageCPU, 0, 0, CPU_IMAGE_SIZE - 1, CPU_IMAGE_SIZE - 1, RED);

	// Draw 2 horizontal lines
	DrawLineX(&gImageCPU, 100, 200, 400, RED);
	DrawLineX(&gImageCPU, 200, 200, 400, RED);

	// Draw 2 vertical linesa
	DrawLineY(&gImageCPU, 150, 100, 300, BLUE);
	DrawLineY(&gImageCPU, 400, 100, 300, BLUE);

	// Draw a rectangle in the centre of your screen and outline it
	DrawRect(&gImageCPU, 200, 200, 100, 80, CYAN);
	DrawRectLines(&gImageCPU, 200, 200, 100, 80, YELLOW);

	// Draw a circle at your mouse cursor and outline it
	DrawCircleLines(&gImageCPU, 50, 300, 50, YELLOW);


	// Draw a line connecting the above two shapes
	DrawLineX(&gImageCPU, 270, 80, 300, GREEN);

}

// Fast way of rendering a circle -- "rasterization" - instead of evaluating every pixel, only evaluate the pixel's within the circle!
// Moreover, the evaluation is extremely cheap since its just a bunch of different-sized scanlines
void Example2()
{
	DrawCircle(&gImageCPU, 400, 256, 50, MAGENTA);
}

// Slow way of rendering a circle -- evaluated for every pixel even if the pixel is not within the circle!
// Moreover, the evaluation is extremely expensive given the square-root calculation in the circle's SDF.
void Example1()
{
	for (int y = 0; y < CPU_IMAGE_SIZE; y++)
	{
		for (int x = 0; x < CPU_IMAGE_SIZE; x++)
		{
			Vector2 uv = { x, y };
			uv /= CPU_IMAGE_SIZE;
			uv = uv * 2.0f - 1.0f;

			float c = sdCircle(uv, 0.75f);
			Vector3 rgb = V3_ONE * step(0.0f, c);

			Color color = Float3ToColor(&rgb.x);
			SetPixel(&gImageCPU, x, y, color);
		}
	}
}

float sdCircle(Vector2 p, float r)
{
	return Length(p) - r;
}

float step(float edge, float x)
{
	return x < edge ? 0.0f : 1.0f;
}
