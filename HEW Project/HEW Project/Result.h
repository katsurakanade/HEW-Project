#pragma once

#define RANKING_MAX		(5)
#define NUMBER_WIDTH  (300)
#define NUMBER_HEIGHT (300)


void Init_Result();
void Uninit_Result();
void Update_Result();
void Draw_Result();

void Ranking_Sort(double score);
void Ranking_Read();


