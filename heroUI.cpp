#pragma once

#include "heroUI.h"
#include <vector>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "globalVariables.h"
#include "map.h"
#include <random>

//buffer data
GLuint uiVAO, uiVBO, uiEBO, uiInstanceVBO;

//container for the data
std::vector<InstanceData> uiInstances;

void populateUI() {
	InstanceData instance;
	//NATURE HERO UI
	//Health bar main UI index 0
	instance.position = glm::vec3(680.0f, 1030.0f, 0.0f);
	instance.texturePosition = glm::vec2(1322.0f, 8192.0f);
	instance.textureSize = glm::vec2(500.0f, 100.0f);
	instance.scale = glm::vec3(1.0f, 0.2f, 0.0f);
	uiInstances.push_back(instance);

	//Health mini bars
	for (int i = 0; i < 31; i++) {
		instance.position = glm::vec3(651.50f, 9038.50f, 0.001f); // position should be 651.50f, 1030.50f in game
		instance.texturePosition = glm::vec2(651.0f, 8192.0f - (439.0f + i * 19.0f)); // goes up every 19.0f
		instance.textureSize = glm::vec2(400.0f, 16.0f);
		instance.scale = glm::vec3(0.8f, 0.032f, 0.0f);
		uiInstances.push_back(instance);
	}

	//Health points
	for (int i = 0; i < 31; i++) {
		instance.position = glm::vec3(883.50f, 9040.0f, 0.001f); // position should be 883.50 and 1040
		instance.texturePosition = glm::vec2(2.0f + i * 129.0f, 8192.0f - 8066.0f);
		instance.textureSize = glm::vec2(124.0f, 124.0f);
		instance.scale = glm::vec3(0.09f, 0.09f, 0.0f);
		uiInstances.push_back(instance);
	}

	//Mana regeneration globes and empty globe
	for (int i = 0; i < 12; i++) {
		instance.position = glm::vec3(883.50f, 9040.0f, 0.002f); // position should be 883.50 and 1040
		instance.texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f);
		instance.textureSize = glm::vec2(32.0f, 28.0f);
		instance.scale = glm::vec3(0.064f, 0.056f, 0.0f);
		uiInstances.push_back(instance);
	}

	//spellbook
	//main UI  index 75
	instance.position = glm::vec3(400.0f, 8000.0f, 0.002f); // 80.0f on the Y
	instance.texturePosition = glm::vec2(1949.0f, 8192.0f - 3118.0f);
	instance.textureSize = glm::vec2(767.0f, 192.0f);
	instance.scale = glm::vec3(667.0f /quadSize, 162.0f / quadSize, 0.0f);
	uiInstances.push_back(instance);
	//pages index 76
	instance.position = glm::vec3(400.0f, 8000.0f, 0.002f); // 60.0f on the Y
	instance.texturePosition = glm::vec2(1922.0f, 8192.0f - 2992.0f);
	instance.textureSize = glm::vec2(813.0f, 125.0f);
	instance.scale = glm::vec3(700.0f / quadSize, 105.0f / quadSize, 0.0f);
	uiInstances.push_back(instance);
}

void createUIBars() {
	glGenVertexArrays(1, &uiVAO);
	glBindVertexArray(uiVAO);

	glGenBuffers(1, &uiVBO);
	glBindBuffer(GL_ARRAY_BUFFER, uiVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &uiEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadIndices), quadIndices, GL_STATIC_DRAW);

	glGenBuffers(1, &uiInstanceVBO);
	glBindBuffer(GL_ARRAY_BUFFER, uiInstanceVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(InstanceData) * uiInstances.size(), uiInstances.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(InstanceData), (void*)0);
	glEnableVertexAttribArray(2);
	glVertexAttribDivisor(2, 1);

	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(InstanceData), (void*)(sizeof(glm::vec3)));
	glEnableVertexAttribArray(3);
	glVertexAttribDivisor(3, 1);

	glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, sizeof(InstanceData), (void*)(sizeof(glm::vec3) + sizeof(glm::vec2)));
	glEnableVertexAttribArray(4);
	glVertexAttribDivisor(4, 1);

	glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(InstanceData), (void*)(sizeof(glm::vec3) + sizeof(glm::vec2) + sizeof(glm::vec2)));
	glEnableVertexAttribArray(5);
	glVertexAttribDivisor(5, 1);

	//Unbind
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void drawUI() {
	glBindVertexArray(uiVAO);
	glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, static_cast<GLsizei>(uiInstances.size()));
	glBindVertexArray(0);
}

void updateUI(Hero& hero) {
	//health bars & health points
	switch (hero.health) {
	case 30:
		uiInstances[1].position = glm::vec3(651.50f, 1038.50f, 0.001f);
		uiInstances[62].position = glm::vec3(883.50f, 1040.0f, 0.001f);
		break;
	case 29:
		uiInstances[2].position = glm::vec3(651.50f, 1038.50f, 0.001f);
		uiInstances[61].position = glm::vec3(883.50f, 1040.0f, 0.001f);
		break;
	case 28:
		uiInstances[3].position = glm::vec3(651.50f, 1038.50f, 0.001f);
		uiInstances[60].position = glm::vec3(883.50f, 1040.0f, 0.001f);
		break;
	case 27:
		uiInstances[4].position = glm::vec3(651.50f, 1038.50f, 0.001f);
		uiInstances[59].position = glm::vec3(883.50f, 1040.0f, 0.001f);
		break;
	case 26:
		uiInstances[5].position = glm::vec3(651.50f, 1038.50f, 0.001f);
		uiInstances[58].position = glm::vec3(883.50f, 1040.0f, 0.001f);
		break;
	case 25:
		uiInstances[6].position = glm::vec3(651.50f, 1038.50f, 0.001f);
		uiInstances[57].position = glm::vec3(883.50f, 1040.0f, 0.001f);
		break;
	case 24:
		uiInstances[7].position = glm::vec3(651.50f, 1038.50f, 0.001f);
		uiInstances[56].position = glm::vec3(883.50f, 1040.0f, 0.001f);
		break;
	case 23:
		uiInstances[8].position = glm::vec3(651.50f, 1038.50f, 0.001f);
		uiInstances[55].position = glm::vec3(883.50f, 1040.0f, 0.001f);
		break;
	case 22:
		uiInstances[9].position = glm::vec3(651.50f, 1038.50f, 0.001f);
		uiInstances[54].position = glm::vec3(883.50f, 1040.0f, 0.001f);
		break;
	case 21:
		uiInstances[10].position = glm::vec3(651.50f, 1038.50f, 0.001f);
		uiInstances[53].position = glm::vec3(883.50f, 1040.0f, 0.001f);
		break;
	case 20:
		uiInstances[11].position = glm::vec3(651.50f, 1038.50f, 0.001f);
		uiInstances[52].position = glm::vec3(883.50f, 1040.0f, 0.001f);
		break;
	case 19:
		uiInstances[12].position = glm::vec3(651.50f, 1038.50f, 0.001f);
		uiInstances[51].position = glm::vec3(883.50f, 1040.0f, 0.001f);
		break;
	case 18:
		uiInstances[13].position = glm::vec3(651.50f, 1038.50f, 0.001f);
		uiInstances[50].position = glm::vec3(883.50f, 1040.0f, 0.001f);
		break;
	case 17:
		uiInstances[14].position = glm::vec3(651.50f, 1038.50f, 0.001f);
		uiInstances[49].position = glm::vec3(883.50f, 1040.0f, 0.001f);
		break;
	case 16:
		uiInstances[15].position = glm::vec3(651.50f, 1038.50f, 0.001f);
		uiInstances[48].position = glm::vec3(883.50f, 1040.0f, 0.001f);
		break;
	case 15:
		uiInstances[16].position = glm::vec3(651.50f, 1038.50f, 0.001f);
		uiInstances[47].position = glm::vec3(883.50f, 1040.0f, 0.001f);
		break;
	case 14:
		uiInstances[17].position = glm::vec3(651.50f, 1038.50f, 0.001f);
		uiInstances[46].position = glm::vec3(883.50f, 1040.0f, 0.001f);
		break;
	case 13:
		uiInstances[18].position = glm::vec3(651.50f, 1038.50f, 0.001f);
		uiInstances[45].position = glm::vec3(883.50f, 1040.0f, 0.001f);
		break;
	case 12:
		uiInstances[19].position = glm::vec3(651.50f, 1038.50f, 0.001f);
		uiInstances[44].position = glm::vec3(883.50f, 1040.0f, 0.001f);
		break;
	case 11:
		uiInstances[20].position = glm::vec3(651.50f, 1038.50f, 0.001f);
		uiInstances[43].position = glm::vec3(883.50f, 1040.0f, 0.001f);
		break;
	case 10:
		uiInstances[21].position = glm::vec3(651.50f, 1038.50f, 0.001f);
		uiInstances[42].position = glm::vec3(883.50f, 1040.0f, 0.001f);
		break;
	case 9:
		uiInstances[22].position = glm::vec3(651.50f, 1038.50f, 0.001f);
		uiInstances[41].position = glm::vec3(883.50f, 1040.0f, 0.001f);
		break;
	case 8:
		uiInstances[23].position = glm::vec3(651.50f, 1038.50f, 0.001f);
		uiInstances[40].position = glm::vec3(883.50f, 1040.0f, 0.001f);
		break;
	case 7:
		uiInstances[24].position = glm::vec3(651.50f, 1038.50f, 0.001f);
		uiInstances[39].position = glm::vec3(883.50f, 1040.0f, 0.001f);
		break;
	case 6:
		uiInstances[25].position = glm::vec3(651.50f, 1038.50f, 0.001f);
		uiInstances[38].position = glm::vec3(883.50f, 1040.0f, 0.001f);
		break;
	case 5:
		uiInstances[26].position = glm::vec3(651.50f, 1038.50f, 0.001f);
		uiInstances[37].position = glm::vec3(883.50f, 1040.0f, 0.001f);
		break;
	case 4:
		uiInstances[27].position = glm::vec3(651.50f, 1038.50f, 0.001f);
		uiInstances[36].position = glm::vec3(883.50f, 1040.0f, 0.001f);
		break;
	case 3:
		uiInstances[28].position = glm::vec3(651.50f, 1038.50f, 0.001f);
		uiInstances[35].position = glm::vec3(883.50f, 1040.0f, 0.001f);
		break;
	case 2:
		uiInstances[29].position = glm::vec3(651.50f, 1038.50f, 0.001f);
		uiInstances[34].position = glm::vec3(883.50f, 1040.0f, 0.001f);
		break;
	case 1:
		uiInstances[30].position = glm::vec3(651.50f, 1038.50f, 0.001f);
		uiInstances[33].position = glm::vec3(883.50f, 1040.0f, 0.001f);
		break;
	case 0:
		uiInstances[31].position = glm::vec3(651.50f, 1038.50f, 0.001f);
		uiInstances[32].position = glm::vec3(883.50f, 1040.0f, 0.001f);
		break;
	default:
		if (hero.health < 0) {
			uiInstances[31].position = glm::vec3(651.50f, 1038.50f, 0.001f);
			uiInstances[32].position = glm::vec3(883.50f, 1040.0f, 0.001f);
		}
		break;
	}

	switch (hero.totalMana) {
	case 1:
		uiInstances[63].position = glm::vec3(835.50f, 1013.0f, 0.002f);
		break;
	case 2:
		uiInstances[64].position = glm::vec3(805.50f, 1013.0f, 0.002f);
		break;
	case 3:
		uiInstances[65].position = glm::vec3(775.5f, 1013.0f, 0.002f);
		break;
	case 4:
		uiInstances[66].position = glm::vec3(737.50f, 1013.0f, 0.002f);
		break;
	case 5:
		uiInstances[67].position = glm::vec3(707.50f, 1013.0f, 0.002f);
		break;
	case 6:
		uiInstances[68].position = glm::vec3(677.50, 1013.0f, 0.002f);
		break;
	case 7:
		uiInstances[69].position = glm::vec3(639.50f, 1013.0f, 0.002f);
		break;
	case 8:
		uiInstances[70].position = glm::vec3(609.50f, 1013.0f, 0.002f);
		break;
	case 9:
		uiInstances[71].position = glm::vec3(579.50f, 1013.0f, 0.002f);
		break;
	case 10:
		uiInstances[72].position = glm::vec3(541.50f, 1013.0f, 0.002f);
		break;
	case 11:
		uiInstances[73].position = glm::vec3(511.50f, 1013.0f, 0.002f);
		break;
	case 12:
		uiInstances[74].position = glm::vec3(481.50f, 1013.0f, 0.002f);
		break;
	default:
		if (hero.totalMana == 0) {
			//
		}
		break;
	}
	glBindBuffer(GL_ARRAY_BUFFER, uiInstanceVBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(InstanceData)* uiInstances.size(), uiInstances.data());
	glBindVertexArray(uiVAO);
	//update mana regen
	//1st crystal
	if (hero.currentMana < 0.1f) {
		uiInstances[63].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f);
		uiInstances[64].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //2nd crystal empty
		uiInstances[65].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //3rd crystal empty
		uiInstances[66].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //4th crystal empty
		uiInstances[67].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //5th crystal empty
		uiInstances[68].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //6th crystal empty
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
	}
	else if (hero.currentMana < 0.2f) {
		uiInstances[63].texturePosition = glm::vec2(1478.0f, 8192.0f - 209.0f);
		uiInstances[64].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //2nd crystal empty
		uiInstances[65].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //3rd crystal empty
		uiInstances[66].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //4th crystal empty
		uiInstances[67].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //5th crystal empty
		uiInstances[68].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //6th crystal empty
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
	}
	else if (hero.currentMana < 0.3f) {
		uiInstances[63].texturePosition = glm::vec2(1443.0f, 8192.0f - 209.0f);
		uiInstances[64].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //2nd crystal empty
		uiInstances[65].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //3rd crystal empty
		uiInstances[66].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //4th crystal empty
		uiInstances[67].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //5th crystal empty
		uiInstances[68].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //6th crystal empty
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
	}
	else if (hero.currentMana < 0.4f) {
		uiInstances[63].texturePosition = glm::vec2(1408.0f, 8192.0f - 209.0f);
		uiInstances[64].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //2nd crystal empty
		uiInstances[65].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //3rd crystal empty
		uiInstances[66].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //4th crystal empty
		uiInstances[67].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //5th crystal empty
		uiInstances[68].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //6th crystal empty
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
	}
	else if (hero.currentMana < 0.5f) {
		uiInstances[63].texturePosition = glm::vec2(1373.0f, 8192.0f - 209.0f);
		uiInstances[64].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //2nd crystal empty
		uiInstances[65].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //3rd crystal empty
		uiInstances[66].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //4th crystal empty
		uiInstances[67].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //5th crystal empty
		uiInstances[68].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //6th crystal empty
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
	}
	else if (hero.currentMana < 0.6f) {
		uiInstances[63].texturePosition = glm::vec2(1338.0f, 8192.0f - 209.0f);
		uiInstances[64].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //2nd crystal empty
		uiInstances[65].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //3rd crystal empty
		uiInstances[66].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //4th crystal empty
		uiInstances[67].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //5th crystal empty
		uiInstances[68].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //6th crystal empty
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
	}
	else if (hero.currentMana < 0.7f) {
		uiInstances[63].texturePosition = glm::vec2(1303.0f, 8192.0f - 209.0f);
		uiInstances[64].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //2nd crystal empty
		uiInstances[65].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //3rd crystal empty
		uiInstances[66].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //4th crystal empty
		uiInstances[67].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //5th crystal empty
		uiInstances[68].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //6th crystal empty
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
	}
	else if (hero.currentMana < 0.8f) {
		uiInstances[63].texturePosition = glm::vec2(1268.0f, 8192.0f - 209.0f);
		uiInstances[64].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //2nd crystal empty
		uiInstances[65].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //3rd crystal empty
		uiInstances[66].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //4th crystal empty
		uiInstances[67].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //5th crystal empty
		uiInstances[68].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //6th crystal empty
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
	}
	else if (hero.currentMana < 0.9f) {
		uiInstances[63].texturePosition = glm::vec2(1233.0f, 8192.0f - 209.0f);
		uiInstances[64].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //2nd crystal empty
		uiInstances[65].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //3rd crystal empty
		uiInstances[66].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //4th crystal empty
		uiInstances[67].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //5th crystal empty
		uiInstances[68].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //6th crystal empty
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
	}
	else if (hero.currentMana < 1.0f) {
		uiInstances[63].texturePosition = glm::vec2(1198.0f, 8192.0f - 209.0f);
		uiInstances[64].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //2nd crystal empty
		uiInstances[65].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //3rd crystal empty
		uiInstances[66].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //4th crystal empty
		uiInstances[67].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //5th crystal empty
		uiInstances[68].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //6th crystal empty
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
	}
	else if (hero.currentMana < 1.1f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //2nd crystal empty
		uiInstances[65].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //3rd crystal empty
		uiInstances[66].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //4th crystal empty
		uiInstances[67].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //5th crystal empty
		uiInstances[68].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //6th crystal empty
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
	}
	//2nd crystal
	else if (hero.currentMana < 1.2f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[64].texturePosition = glm::vec2(1478.0f, 8192.0f - 209.0f);
		uiInstances[65].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //3rd crystal empty
		uiInstances[66].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //4th crystal empty
		uiInstances[67].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //5th crystal empty
		uiInstances[68].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //6th crystal empty
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
	}
	else if (hero.currentMana < 1.3f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[64].texturePosition = glm::vec2(1443.0f, 8192.0f - 209.0f);
		uiInstances[65].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //3rd crystal empty
		uiInstances[66].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //4th crystal empty
		uiInstances[67].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //5th crystal empty
		uiInstances[68].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //6th crystal empty
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
	}
	else if (hero.currentMana < 1.4f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[64].texturePosition = glm::vec2(1408.0f, 8192.0f - 209.0f);
		uiInstances[65].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //3rd crystal empty
		uiInstances[66].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //4th crystal empty
		uiInstances[67].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //5th crystal empty
		uiInstances[68].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //6th crystal empty
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
	}
	else if (hero.currentMana < 1.5f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[64].texturePosition = glm::vec2(1373.0f, 8192.0f - 209.0f);
		uiInstances[65].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //3rd crystal empty
		uiInstances[66].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //4th crystal empty
		uiInstances[67].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //5th crystal empty
		uiInstances[68].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //6th crystal empty
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
	}
	else if (hero.currentMana < 1.6f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[64].texturePosition = glm::vec2(1338.0f, 8192.0f - 209.0f);
		uiInstances[65].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //3rd crystal empty
		uiInstances[66].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //4th crystal empty
		uiInstances[67].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //5th crystal empty
		uiInstances[68].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //6th crystal empty
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
	}
	else if (hero.currentMana < 1.7f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[64].texturePosition = glm::vec2(1303.0f, 8192.0f - 209.0f);
		uiInstances[65].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //3rd crystal empty
		uiInstances[66].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //4th crystal empty
		uiInstances[67].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //5th crystal empty
		uiInstances[68].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //6th crystal empty
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
	}
	else if (hero.currentMana < 1.8f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[64].texturePosition = glm::vec2(1268.0f, 8192.0f - 209.0f);
		uiInstances[65].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //3rd crystal empty
		uiInstances[66].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //4th crystal empty
		uiInstances[67].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //5th crystal empty
		uiInstances[68].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //6th crystal empty
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
	}
	else if (hero.currentMana < 1.9f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[64].texturePosition = glm::vec2(1233.0f, 8192.0f - 209.0f);
		uiInstances[65].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //3rd crystal empty
		uiInstances[66].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //4th crystal empty
		uiInstances[67].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //5th crystal empty
		uiInstances[68].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //6th crystal empty
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
	}
	else if (hero.currentMana < 2.0f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[64].texturePosition = glm::vec2(1198.0f, 8192.0f - 209.0f);
		uiInstances[65].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //3rd crystal empty
		uiInstances[66].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //4th crystal empty
		uiInstances[67].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //5th crystal empty
		uiInstances[68].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //6th crystal empty
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
	}
	else if (hero.currentMana < 2.1f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //3rd crystal empty
		uiInstances[66].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //4th crystal empty
		uiInstances[67].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //5th crystal empty
		uiInstances[68].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //6th crystal empty
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
	}
	//3rd crystal
	else if (hero.currentMana < 2.2f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); 
		uiInstances[65].texturePosition = glm::vec2(1478.0f, 8192.0f - 209.0f); 
		uiInstances[66].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //4th crystal empty
		uiInstances[67].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //5th crystal empty
		uiInstances[68].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //6th crystal empty
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
	}
	else if (hero.currentMana < 2.3f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[65].texturePosition = glm::vec2(1443.0f, 8192.0f - 209.0f);
		uiInstances[66].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //4th crystal empty
		uiInstances[67].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //5th crystal empty
		uiInstances[68].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //6th crystal empty
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
	}
	else if (hero.currentMana < 2.4f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[65].texturePosition = glm::vec2(1408.0f, 8192.0f - 209.0f);
		uiInstances[66].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //4th crystal empty
		uiInstances[67].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //5th crystal empty
		uiInstances[68].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //6th crystal empty
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
	}
	else if (hero.currentMana < 2.5f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[65].texturePosition = glm::vec2(1373.0f, 8192.0f - 209.0f);
		uiInstances[66].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //4th crystal empty
		uiInstances[67].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //5th crystal empty
		uiInstances[68].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //6th crystal empty
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
	}
	else if (hero.currentMana < 2.6f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[65].texturePosition = glm::vec2(1338.0f, 8192.0f - 209.0f);
		uiInstances[66].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //4th crystal empty
		uiInstances[67].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //5th crystal empty
		uiInstances[68].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //6th crystal empty
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
	}
	else if (hero.currentMana < 2.7f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[65].texturePosition = glm::vec2(1303.0f, 8192.0f - 209.0f);
		uiInstances[66].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //4th crystal empty
		uiInstances[67].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //5th crystal empty
		uiInstances[68].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //6th crystal empty
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
	}
	else if (hero.currentMana < 2.8f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[65].texturePosition = glm::vec2(1268.0f, 8192.0f - 209.0f);
		uiInstances[66].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //4th crystal empty
		uiInstances[67].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //5th crystal empty
		uiInstances[68].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //6th crystal empty
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
	}
	else if (hero.currentMana < 2.9f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[65].texturePosition = glm::vec2(1233.0f, 8192.0f - 209.0f);
		uiInstances[66].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //4th crystal empty
		uiInstances[67].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //5th crystal empty
		uiInstances[68].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //6th crystal empty
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
	}
	else if (hero.currentMana < 3.0f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[65].texturePosition = glm::vec2(1198.0f, 8192.0f - 209.0f);
		uiInstances[66].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //4th crystal empty
		uiInstances[67].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //5th crystal empty
		uiInstances[68].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //6th crystal empty
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
	}
	else if (hero.currentMana < 3.1f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //4th crystal empty
		uiInstances[67].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //5th crystal empty
		uiInstances[68].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //6th crystal empty
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
	}
	//4th crystal
	else if (hero.currentMana < 3.2f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1478.0f, 8192.0f - 209.0f);
		uiInstances[67].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //5th crystal empty
		uiInstances[68].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //6th crystal empty
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
	}
	else if (hero.currentMana < 3.3f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1443.0f, 8192.0f - 209.0f);
		uiInstances[67].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //5th crystal empty
		uiInstances[68].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //6th crystal empty
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
	}
	else if (hero.currentMana < 3.4f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1408.0f, 8192.0f - 209.0f);
		uiInstances[67].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //5th crystal empty
		uiInstances[68].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //6th crystal empty
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
	}
	else if (hero.currentMana < 3.5f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1373.0f, 8192.0f - 209.0f);
		uiInstances[67].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //5th crystal empty
		uiInstances[68].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //6th crystal empty
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
	}
	else if (hero.currentMana < 3.6f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1338.0f, 8192.0f - 209.0f);
		uiInstances[67].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //5th crystal empty
		uiInstances[68].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //6th crystal empty
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
	}
	else if (hero.currentMana < 3.7f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1303.0f, 8192.0f - 209.0f);
		uiInstances[67].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //5th crystal empty
		uiInstances[68].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //6th crystal empty
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
	}
	else if (hero.currentMana < 3.8f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1268.0f, 8192.0f - 209.0f);
		uiInstances[67].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //5th crystal empty
		uiInstances[68].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //6th crystal empty
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
	}
	else if (hero.currentMana < 3.9f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1233.0f, 8192.0f - 209.0f);
		uiInstances[67].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //5th crystal empty
		uiInstances[68].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //6th crystal empty
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
	}
	else if (hero.currentMana < 4.0f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1198.0f, 8192.0f - 209.0f);
		uiInstances[67].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //5th crystal empty
		uiInstances[68].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //6th crystal empty
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
	}
	else if (hero.currentMana < 4.1f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //4th crystal full
		uiInstances[67].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //5th crystal empty
		uiInstances[68].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //6th crystal empty
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
	}
	//5th crystal
	else if (hero.currentMana < 4.2f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //4th crystal full
		uiInstances[67].texturePosition = glm::vec2(1478.0f, 8192.0f - 209.0f);
		uiInstances[68].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //6th crystal empty
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
	}
	else if (hero.currentMana < 4.3f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[67].texturePosition = glm::vec2(1443.0f, 8192.0f - 209.0f);
		uiInstances[68].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //6th crystal empty
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
	}
	else if (hero.currentMana < 4.4f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[67].texturePosition = glm::vec2(1408.0f, 8192.0f - 209.0f);
		uiInstances[68].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //6th crystal empty
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
	}
	else if (hero.currentMana < 4.5f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[67].texturePosition = glm::vec2(1373.0f, 8192.0f - 209.0f);
		uiInstances[68].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //6th crystal empty
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
	}
	else if (hero.currentMana < 4.6f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[67].texturePosition = glm::vec2(1338.0f, 8192.0f - 209.0f);
		uiInstances[68].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //6th crystal empty
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
	}
	else if (hero.currentMana < 4.7f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[67].texturePosition = glm::vec2(1303.0f, 8192.0f - 209.0f);
		uiInstances[68].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //6th crystal empty
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
	}
	else if (hero.currentMana < 4.8f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[67].texturePosition = glm::vec2(1268.0f, 8192.0f - 209.0f);
		uiInstances[68].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //6th crystal empty
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
	}
	else if (hero.currentMana < 4.9f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[67].texturePosition = glm::vec2(1233.0f, 8192.0f - 209.0f);
		uiInstances[68].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //6th crystal empty
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
	}
	else if (hero.currentMana < 5.0f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[67].texturePosition = glm::vec2(1198.0f, 8192.0f - 209.0f);
		uiInstances[68].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //6th crystal empty
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
	}
	else if (hero.currentMana < 5.1f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //4th crystal full
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //5th crystal full
		uiInstances[68].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //6th crystal empty
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
	}
	//6th crystal
	else if (hero.currentMana < 5.2f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //4th crystal full
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //5th crystal full
		uiInstances[68].texturePosition = glm::vec2(1478.0f, 8192.0f - 209.0f); //6th crystal full
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
	else if (hero.currentMana < 5.3f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[68].texturePosition = glm::vec2(1443.0f, 8192.0f - 209.0f); //6th crystal full
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
	else if (hero.currentMana < 5.4f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[68].texturePosition = glm::vec2(1408.0f, 8192.0f - 209.0f);
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
	else if (hero.currentMana < 5.5f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[68].texturePosition = glm::vec2(1373.0f, 8192.0f - 209.0f);
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
	else if (hero.currentMana < 5.6f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[68].texturePosition = glm::vec2(1338.0f, 8192.0f - 209.0f);
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
	else if (hero.currentMana < 5.7f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[68].texturePosition = glm::vec2(1303.0f, 8192.0f - 209.0f);
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
	else if (hero.currentMana < 5.8f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[68].texturePosition = glm::vec2(1268.0f, 8192.0f - 209.0f);
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
	else if (hero.currentMana < 5.9f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[68].texturePosition = glm::vec2(1233.0f, 8192.0f - 209.0f);
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
	else if (hero.currentMana < 6.0f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[68].texturePosition = glm::vec2(1198.0f, 8192.0f - 209.0f);
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
	else if (hero.currentMana < 6.1f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //4th crystal full
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //5th crystal full
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //6th crystal full
		uiInstances[69].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //7th crystal empty
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
		//7th crystal
	else if (hero.currentMana < 6.2f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //4th crystal full
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //5th crystal full
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //6th crystal full
		uiInstances[69].texturePosition = glm::vec2(1478.0f, 8192.0f - 209.0f); 
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
	else if (hero.currentMana < 6.3f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //6th crystal full
		uiInstances[69].texturePosition = glm::vec2(1443.0f, 8192.0f - 209.0f); //6th crystal full
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
	else if (hero.currentMana < 6.4f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[69].texturePosition = glm::vec2(1408.0f, 8192.0f - 209.0f);
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
	else if (hero.currentMana < 6.5f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[69].texturePosition = glm::vec2(1373.0f, 8192.0f - 209.0f);
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
	else if (hero.currentMana < 6.6f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[69].texturePosition = glm::vec2(1338.0f, 8192.0f - 209.0f);
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
	else if (hero.currentMana < 6.7f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[69].texturePosition = glm::vec2(1303.0f, 8192.0f - 209.0f);
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
	else if (hero.currentMana < 6.8f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[69].texturePosition = glm::vec2(1268.0f, 8192.0f - 209.0f);
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
	else if (hero.currentMana < 6.9f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[69].texturePosition = glm::vec2(1233.0f, 8192.0f - 209.0f);
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
	else if (hero.currentMana < 7.0f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[69].texturePosition = glm::vec2(1198.0f, 8192.0f - 209.0f);
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
	else if (hero.currentMana < 7.1f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //4th crystal full
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //5th crystal full
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //6th crystal full
		uiInstances[69].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //7th crystal full
		uiInstances[70].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //8th crystal empty
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
		//8th crystal
	else if (hero.currentMana < 7.2f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //4th crystal full
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //5th crystal full
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //6th crystal full
		uiInstances[69].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //7th crystal full
		uiInstances[70].texturePosition = glm::vec2(1478.0f, 8192.0f - 209.0f); //7th crystal full
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
	else if (hero.currentMana < 7.3f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //6th crystal full
		uiInstances[69].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //6th crystal full
		uiInstances[70].texturePosition = glm::vec2(1443.0f, 8192.0f - 209.0f); //6th crystal full
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
	else if (hero.currentMana < 7.4f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[69].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[70].texturePosition = glm::vec2(1408.0f, 8192.0f - 209.0f);
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
	else if (hero.currentMana < 7.5f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[69].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[70].texturePosition = glm::vec2(1373.0f, 8192.0f - 209.0f);
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
	else if (hero.currentMana < 7.6f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[69].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[70].texturePosition = glm::vec2(1338.0f, 8192.0f - 209.0f);
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
	else if (hero.currentMana < 7.7f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[69].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[70].texturePosition = glm::vec2(1303.0f, 8192.0f - 209.0f);
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
	else if (hero.currentMana < 7.8f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[69].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[70].texturePosition = glm::vec2(1268.0f, 8192.0f - 209.0f);
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
	else if (hero.currentMana < 7.9f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[69].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[70].texturePosition = glm::vec2(1233.0f, 8192.0f - 209.0f);
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
	else if (hero.currentMana < 8.0f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[69].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[70].texturePosition = glm::vec2(1198.0f, 8192.0f - 209.0f);
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
	else if (hero.currentMana < 8.1f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //4th crystal full
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //5th crystal full
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //6th crystal full
		uiInstances[69].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //7th crystal full
		uiInstances[70].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //8th crystal full
		uiInstances[71].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //9th crystal empty
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
		//9th crystal
	else if (hero.currentMana < 8.2f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //4th crystal full
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //5th crystal full
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //6th crystal full
		uiInstances[69].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //7th crystal full
		uiInstances[70].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //8th crystal full
		uiInstances[71].texturePosition = glm::vec2(1478.0f, 8192.0f - 209.0f); //9th crystal
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
	else if (hero.currentMana < 8.3f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //6th crystal full
		uiInstances[69].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //6th crystal full
		uiInstances[70].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //6th crystal full
		uiInstances[71].texturePosition = glm::vec2(1443.0f, 8192.0f - 209.0f); //6th crystal full
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
	else if (hero.currentMana < 8.4f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[69].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[70].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[71].texturePosition = glm::vec2(1408.0f, 8192.0f - 209.0f);
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
	else if (hero.currentMana < 8.5f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[69].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[70].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[71].texturePosition = glm::vec2(1373.0f, 8192.0f - 209.0f);
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
	else if (hero.currentMana < 8.6f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[69].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[70].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[71].texturePosition = glm::vec2(1338.0f, 8192.0f - 209.0f);
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
	else if (hero.currentMana < 8.7f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[69].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[70].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[71].texturePosition = glm::vec2(1303.0f, 8192.0f - 209.0f);
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
	else if (hero.currentMana < 8.8f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[69].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[70].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[71].texturePosition = glm::vec2(1268.0f, 8192.0f - 209.0f);
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
	else if (hero.currentMana < 8.9f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[69].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[70].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[71].texturePosition = glm::vec2(1233.0f, 8192.0f - 209.0f);
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
	else if (hero.currentMana < 9.0f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[69].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[70].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f);
		uiInstances[71].texturePosition = glm::vec2(1198.0f, 8192.0f - 209.0f);
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
	else if (hero.currentMana < 9.1f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //4th crystal full
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //5th crystal full
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //6th crystal full
		uiInstances[69].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //7th crystal full
		uiInstances[70].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //8th crystal full
		uiInstances[71].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //9th crystal full
		uiInstances[72].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //10th crystal empty
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
		//10th crystal
	else if (hero.currentMana < 9.2f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //4th crystal full
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //5th crystal full
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //6th crystal full
		uiInstances[69].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //7th crystal full
		uiInstances[70].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //8th crystal full
		uiInstances[71].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //9th crystal full
		uiInstances[72].texturePosition = glm::vec2(1478.0f, 8192.0f - 209.0f); //10th crystal
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
	else if (hero.currentMana < 9.3f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //4th crystal full
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //5th crystal full
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //6th crystal full
		uiInstances[69].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //7th crystal full
		uiInstances[70].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //8th crystal full
		uiInstances[71].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //9th crystal full
		uiInstances[72].texturePosition = glm::vec2(1443.0f, 8192.0f - 209.0f); //10th crystal
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
	else if (hero.currentMana < 9.4f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //4th crystal full
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //5th crystal full
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //6th crystal full
		uiInstances[69].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //7th crystal full
		uiInstances[70].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //8th crystal full
		uiInstances[71].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //9th crystal full
		uiInstances[72].texturePosition = glm::vec2(1408.0f, 8192.0f - 209.0f); //10th crystal
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
	else if (hero.currentMana < 9.5f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //4th crystal full
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //5th crystal full
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //6th crystal full
		uiInstances[69].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //7th crystal full
		uiInstances[70].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //8th crystal full
		uiInstances[71].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //9th crystal full
		uiInstances[72].texturePosition = glm::vec2(1373.0f, 8192.0f - 209.0f); //10th crystal
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
	else if (hero.currentMana < 9.6f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //4th crystal full
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //5th crystal full
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //6th crystal full
		uiInstances[69].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //7th crystal full
		uiInstances[70].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //8th crystal full
		uiInstances[71].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //9th crystal full
		uiInstances[72].texturePosition = glm::vec2(1338.0f, 8192.0f - 209.0f); //10th crystal
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
	else if (hero.currentMana < 9.7f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //4th crystal full
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //5th crystal full
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //6th crystal full
		uiInstances[69].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //7th crystal full
		uiInstances[70].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //8th crystal full
		uiInstances[71].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //9th crystal full
		uiInstances[72].texturePosition = glm::vec2(1303.0f, 8192.0f - 209.0f); //10th crystal
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
	else if (hero.currentMana < 9.8f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //4th crystal full
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //5th crystal full
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //6th crystal full
		uiInstances[69].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //7th crystal full
		uiInstances[70].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //8th crystal full
		uiInstances[71].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //9th crystal full
		uiInstances[72].texturePosition = glm::vec2(1268.0f, 8192.0f - 209.0f); //10th crystal
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
	else if (hero.currentMana < 9.9f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //4th crystal full
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //5th crystal full
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //6th crystal full
		uiInstances[69].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //7th crystal full
		uiInstances[70].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //8th crystal full
		uiInstances[71].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //9th crystal full
		uiInstances[72].texturePosition = glm::vec2(1233.0f, 8192.0f - 209.0f); //10th crystal
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
	else if (hero.currentMana < 10.0f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //4th crystal full
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //5th crystal full
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //6th crystal full
		uiInstances[69].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //7th crystal full
		uiInstances[70].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //8th crystal full
		uiInstances[71].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //9th crystal full
		uiInstances[72].texturePosition = glm::vec2(1198.0f, 8192.0f - 209.0f); //10th crystal
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
	else if (hero.currentMana < 10.1f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //4th crystal full
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //5th crystal full
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //6th crystal full
		uiInstances[69].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //7th crystal full
		uiInstances[70].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //8th crystal full
		uiInstances[71].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //9th crystal full
		uiInstances[72].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //10th crystal full
		uiInstances[73].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //11th crystal empty
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
		//11th crystal
	else if (hero.currentMana < 10.2f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //4th crystal full
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //5th crystal full
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //6th crystal full
		uiInstances[69].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //7th crystal full
		uiInstances[70].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //8th crystal full
		uiInstances[71].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //9th crystal full
		uiInstances[72].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //10th crystal full
		uiInstances[73].texturePosition = glm::vec2(1478.0f, 8192.0f - 209.0f); //11th crystal 
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
	else if (hero.currentMana < 10.3f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //4th crystal full
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //5th crystal full
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //6th crystal full
		uiInstances[69].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //7th crystal full
		uiInstances[70].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //8th crystal full
		uiInstances[71].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //9th crystal full
		uiInstances[72].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //10th crystal full
		uiInstances[73].texturePosition = glm::vec2(1443.0f, 8192.0f - 209.0f); //11th crystal
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
	else if (hero.currentMana < 10.4f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //4th crystal full
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //5th crystal full
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //6th crystal full
		uiInstances[69].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //7th crystal full
		uiInstances[70].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //8th crystal full
		uiInstances[71].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //9th crystal full
		uiInstances[72].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //10th crystal
		uiInstances[73].texturePosition = glm::vec2(1408.0f, 8192.0f - 209.0f); //10th crystal
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
	else if (hero.currentMana < 10.5f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //4th crystal full
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //5th crystal full
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //6th crystal full
		uiInstances[69].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //7th crystal full
		uiInstances[70].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //8th crystal full
		uiInstances[71].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //9th crystal full
		uiInstances[72].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //10th crystal
		uiInstances[73].texturePosition = glm::vec2(1373.0f, 8192.0f - 209.0f); //10th crystal
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
	else if (hero.currentMana < 10.6f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //4th crystal full
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //5th crystal full
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //6th crystal full
		uiInstances[69].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //7th crystal full
		uiInstances[70].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //8th crystal full
		uiInstances[71].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //9th crystal full
		uiInstances[72].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //10th crystal
		uiInstances[73].texturePosition = glm::vec2(1338.0f, 8192.0f - 209.0f); //10th crystal
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
	else if (hero.currentMana < 10.7f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //4th crystal full
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //5th crystal full
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //6th crystal full
		uiInstances[69].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //7th crystal full
		uiInstances[70].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //8th crystal full
		uiInstances[71].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //9th crystal full
		uiInstances[72].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //10th crystal
		uiInstances[73].texturePosition = glm::vec2(1303.0f, 8192.0f - 209.0f); //10th crystal
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
	else if (hero.currentMana < 10.8f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //4th crystal full
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //5th crystal full
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //6th crystal full
		uiInstances[69].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //7th crystal full
		uiInstances[70].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //8th crystal full
		uiInstances[71].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //9th crystal full
		uiInstances[72].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //10th crystal
		uiInstances[73].texturePosition = glm::vec2(1268.0f, 8192.0f - 209.0f); //10th crystal
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
	else if (hero.currentMana < 10.9f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //4th crystal full
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //5th crystal full
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //6th crystal full
		uiInstances[69].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //7th crystal full
		uiInstances[70].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //8th crystal full
		uiInstances[71].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //9th crystal full
		uiInstances[72].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //10th crystal
		uiInstances[73].texturePosition = glm::vec2(1233.0f, 8192.0f - 209.0f); //10th crystal
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
	else if (hero.currentMana < 11.0f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //4th crystal full
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //5th crystal full
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //6th crystal full
		uiInstances[69].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //7th crystal full
		uiInstances[70].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //8th crystal full
		uiInstances[71].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //9th crystal full
		uiInstances[72].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //10th crystal
		uiInstances[73].texturePosition = glm::vec2(1198.0f, 8192.0f - 209.0f); //10th crystal
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
	else if (hero.currentMana < 11.1f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //4th crystal full
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //5th crystal full
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //6th crystal full
		uiInstances[69].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //7th crystal full
		uiInstances[70].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //8th crystal full
		uiInstances[71].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //9th crystal full
		uiInstances[72].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //10th crystal full
		uiInstances[73].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //11th crystal full
		uiInstances[74].texturePosition = glm::vec2(1513.0f, 8192.0f - 209.0f); //12th crystal empty
		}
		//12th crystal
	else if (hero.currentMana < 11.2f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //4th crystal full
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //5th crystal full
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //6th crystal full
		uiInstances[69].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //7th crystal full
		uiInstances[70].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //8th crystal full
		uiInstances[71].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //9th crystal full
		uiInstances[72].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //10th crystal full
		uiInstances[73].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //11th crystal full
		uiInstances[74].texturePosition = glm::vec2(1478.0f, 8192.0f - 209.0f); //11th crystal full
		}
	else if (hero.currentMana < 11.3f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //4th crystal full
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //5th crystal full
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //6th crystal full
		uiInstances[69].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //7th crystal full
		uiInstances[70].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //8th crystal full
		uiInstances[71].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //9th crystal full
		uiInstances[72].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //10th crystal full
		uiInstances[73].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //11th crystal
		uiInstances[74].texturePosition = glm::vec2(1443.0f, 8192.0f - 209.0f); //11th crystal
		}
	else if (hero.currentMana < 11.4f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //4th crystal full
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //5th crystal full
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //6th crystal full
		uiInstances[69].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //7th crystal full
		uiInstances[70].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //8th crystal full
		uiInstances[71].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //9th crystal full
		uiInstances[72].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //10th crystal
		uiInstances[73].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //10th crystal
		uiInstances[74].texturePosition = glm::vec2(1408.0f, 8192.0f - 209.0f); //10th crystal
		}
	else if (hero.currentMana < 11.5f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //4th crystal full
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //5th crystal full
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //6th crystal full
		uiInstances[69].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //7th crystal full
		uiInstances[70].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //8th crystal full
		uiInstances[71].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //9th crystal full
		uiInstances[72].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //10th crystal
		uiInstances[73].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //10th crystal
		uiInstances[74].texturePosition = glm::vec2(1373.0f, 8192.0f - 209.0f); //10th crystal
		}
	else if (hero.currentMana < 11.6f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //4th crystal full
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //5th crystal full
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //6th crystal full
		uiInstances[69].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //7th crystal full
		uiInstances[70].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //8th crystal full
		uiInstances[71].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //9th crystal full
		uiInstances[72].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //10th crystal
		uiInstances[73].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //10th crystal
		uiInstances[74].texturePosition = glm::vec2(1338.0f, 8192.0f - 209.0f); //10th crystal
		}
	else if (hero.currentMana < 11.7f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //4th crystal full
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //5th crystal full
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //6th crystal full
		uiInstances[69].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //7th crystal full
		uiInstances[70].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //8th crystal full
		uiInstances[71].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //9th crystal full
		uiInstances[72].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //10th crystal
		uiInstances[73].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //10th crystal
		uiInstances[74].texturePosition = glm::vec2(1303.0f, 8192.0f - 209.0f); //10th crystal
		}
	else if (hero.currentMana < 11.8f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //4th crystal full
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //5th crystal full
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //6th crystal full
		uiInstances[69].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //7th crystal full
		uiInstances[70].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //8th crystal full
		uiInstances[71].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //9th crystal full
		uiInstances[72].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //10th crystal
		uiInstances[73].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //10th crystal
		uiInstances[74].texturePosition = glm::vec2(1268.0f, 8192.0f - 209.0f); //10th crystal
		}
	else if (hero.currentMana < 11.9f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //4th crystal full
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //5th crystal full
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //6th crystal full
		uiInstances[69].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //7th crystal full
		uiInstances[70].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //8th crystal full
		uiInstances[71].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //9th crystal full
		uiInstances[72].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //10th crystal
		uiInstances[73].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //10th crystal
		uiInstances[74].texturePosition = glm::vec2(1233.0f, 8192.0f - 209.0f); //10th crystal
		}
	else if (hero.currentMana < 12.0f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //4th crystal full
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //5th crystal full
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //6th crystal full
		uiInstances[69].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //7th crystal full
		uiInstances[70].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //8th crystal full
		uiInstances[71].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //9th crystal full
		uiInstances[72].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //10th crystal
		uiInstances[73].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //11th crystal
		uiInstances[74].texturePosition = glm::vec2(1198.0f, 8192.0f - 209.0f); //11th crystal
		}
	else if (hero.currentMana < 12.1f) {
		uiInstances[63].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //1st crystal full
		uiInstances[64].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //2nd crystal full
		uiInstances[65].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //3rd crystal full
		uiInstances[66].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //4th crystal full
		uiInstances[67].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //5th crystal full
		uiInstances[68].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //6th crystal full
		uiInstances[69].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //7th crystal full
		uiInstances[70].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //8th crystal full
		uiInstances[71].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //9th crystal full
		uiInstances[72].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //10th crystal full
		uiInstances[73].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //11th crystal full
		uiInstances[74].texturePosition = glm::vec2(1163.0f, 8192.0f - 209.0f); //12th crystal full
		}

	glBindBuffer(GL_ARRAY_BUFFER, uiInstanceVBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(InstanceData) * uiInstances.size(), uiInstances.data());
	glBindVertexArray(uiVAO);
}

void updateSpellBook(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_I)) {
		spellBookUI = mainMenu;
	}
	if (spellBookUI == mainMenu) {
		if (glfwGetKey(window, GLFW_KEY_J)) {
			spellBookUI = spellsPage1;
		}
		else if (glfwGetKey(window, GLFW_KEY_K)) {
			spellBookUI = unitsPage1;
		}
		else if (glfwGetKey(window, GLFW_KEY_L)) {
			spellBookUI = enchantmentsPage1;
		}
	}

	//=================================
	//UPDATE SPELLBOOK UI
	switch (spellBookUI) {
	case mainMenu: {
		uiInstances[75].position.y = 80.0f;
		uiInstances[76].position.y = 9999.0f;
		break;
	}
	case spellsPage1: {
		uiInstances[76].position.y = 60.0f;
		uiInstances[75].position.y = 9999.0f;
		break;
	}
	case spellsPage2: {
		uiInstances[76].position.y = 60.0f;
		uiInstances[75].position.y = 9999.0f;
		break;
	}
	case unitsPage1: {
		uiInstances[76].position.y = 60.0f;
		uiInstances[75].position.y = 9999.0f;
		break;
	}
	case unitsPage2: {
		uiInstances[76].position.y = 60.0f;
		uiInstances[75].position.y = 9999.0f;
		break;
	}
	case enchantmentsPage1: {
		uiInstances[76].position.y = 60.0f;
		uiInstances[75].position.y = 9999.0f;
		break;
	}
	}
}
