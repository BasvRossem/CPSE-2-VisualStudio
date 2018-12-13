#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "actions.hpp"
#include "iostreamOverloaders.hpp"

class movableScreenObject {
protected:
	std::string objectName;
	bool selected = 0;
	sf::Vector2f objectPosition;

public:


	virtual void draw(sf::RenderWindow & window) = 0;
	virtual sf::Rect<float> getCustomGlobalBounds() = 0;
	virtual void writeSave(std::ofstream & output) = 0;
	
	bool getSelect() { return selected; };
	std::string getName() { return objectName; };

	virtual void select(sf::Vector2f mousePosition) {
		if (getCustomGlobalBounds().contains(mousePosition)) {
			selected = !selected;
		}
	}

	virtual void move(sf::Vector2f & delta) {
		if (selected) {
			objectPosition += delta;
		}
	}

};

class rectangleObject : public movableScreenObject {
private:
	sf::RectangleShape rectObject;
	sf::Vector2f objectSize;
	sf::Color objectColor;
public:
	rectangleObject(sf::Vector2f position, sf::Vector2f size, sf::Color color) {
		rectObject.setPosition(position);
		rectObject.setSize(size);
		rectObject.setFillColor(color);

		objectSize = size;
		objectPosition = position;
		objectColor = color;
		objectName = "RECTANGLE";
	}

	void draw(sf::RenderWindow & window) {
		rectObject.setPosition(objectPosition);
		window.draw(rectObject);
	}

	sf::Rect<float> getCustomGlobalBounds() {
		return rectObject.getGlobalBounds();
	}

	virtual void writeSave(std::ofstream & output) {
		output << "(" << rectObject.getPosition().x << "," << rectObject.getPosition().y << ")"
			<< " " << objectName
			<< " ";
		output << objectColor
			<< " " << "(" << objectSize.x << "," << objectSize.y << ")"
			<< std::endl;
	}
};

class circleObject : public movableScreenObject {
private:
	sf::CircleShape circObject;
	float objectSize;
	sf::Color objectColor;
public:
	circleObject(sf::Vector2f position, float size, sf::Color color) {
		circObject.setPosition(position);
		circObject.setRadius(size);
		circObject.setFillColor(color);
		
		objectSize = size;
		objectPosition = position;
		objectColor = color;
		objectName = "CIRCLE";
	}

	void draw(sf::RenderWindow & window) {
		circObject.setPosition(objectPosition);
		window.draw(circObject);
	}

	sf::Rect<float> getCustomGlobalBounds() {
		return circObject.getGlobalBounds();
	}

	virtual void writeSave(std::ofstream & output) {
		output << "(" << circObject.getPosition().x << "," << circObject.getPosition().y << ")"
			<< " " << objectName
			<< " ";
		output << objectColor
			<< " " << objectSize
			<< std::endl;
	}
};

class lineObject : public movableScreenObject {
private:
	sf::Vertex liObject[2];
	sf::Vector2f objectEndPosition;
	sf::Color objectColor;
public:
	lineObject(sf::Vector2f startPosition, sf::Vector2f endPosition, sf::Color color) {
		liObject[0].position = startPosition;
		liObject[1].position = endPosition;
		liObject[0].color = color;
		liObject[1].color = color;
		
		objectPosition = startPosition;
		objectEndPosition = endPosition;
		objectColor = color;
		objectName = "LINE";
	}

	void draw(sf::RenderWindow & window) {
		window.draw(liObject, 2, sf::Lines);
	}

	void select(sf::Vector2f mousePosition) {
		if (getCustomGlobalBounds().contains(mousePosition)) {
			selected = !selected;
		}
	}

	void move(sf::Vector2f & delta) {
		if (selected) {
			liObject[0].position += delta;
			liObject[1].position += delta;
		}
	}

	sf::FloatRect getCustomGlobalBounds(){
		sf::VertexArray linePosition(sf::LinesStrip, 4);
		linePosition[0].position = objectPosition;
		linePosition[1].position = objectEndPosition;
		linePosition[2].position = objectPosition + sf::Vector2f(2,2);
		linePosition[3].position = objectEndPosition + sf::Vector2f(2,2);
		return linePosition.getBounds();
	}

	virtual void writeSave(std::ofstream & output) {
		output << "(" << liObject[0].position.x << "," << liObject[0].position.y << ")"
			<< " " << objectName
			<< " ";
		output << objectColor
			<< " " << "(" << liObject[1].position.x << "," << liObject[1].position.y << ")"
			<< std::endl;
	}

};

class pictureObject : public movableScreenObject {
private:
	sf::Texture objectTexture;
	sf::Sprite objectSprite;
	std::string objectPicture;
public:
	pictureObject(sf::Vector2f position, std::string pictureName) {
		if (!objectTexture.loadFromFile(pictureName)) {
			std::cerr << "Picture with name: " << pictureName << "could not be found" << std::endl;
		}
		objectSprite.setTexture(objectTexture);
		objectSprite.setPosition(position);
		objectPosition = position;
		objectPicture = pictureName;
		objectName = "PICTURE";
	}

	void draw(sf::RenderWindow & window) {
		objectSprite.setPosition(objectPosition);
		window.draw(objectSprite);
	}

	sf::Rect<float> getCustomGlobalBounds() {
		return objectSprite.getGlobalBounds();
	}

	void writeSave(std::ofstream & output) {
		output << '(';
		output << objectSprite.getPosition().x;
		output << ",";
		output << objectSprite.getPosition().y;
		output << ")";
		output << " ";
		output << objectName;
		output << " ";
		output << objectPicture;
		output << std::endl;
	}
};