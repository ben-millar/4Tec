#include <PlayerInput.h>

void PlayerInput::Click(sf::Vector2i t_mouseClick)
{
	Move move = calculateBoardPiece(t_mouseClick);
	notify(move, m_type);
}

//*****************************************************************************

Move PlayerInput::calculateBoardPiece(sf::Vector2i t_mousePos)
{
	uint8_t layer{ 9 }, row{ 9 }, col{ 9 };

	static const sf::Vector2u boardSize =
		TextureManager::getInstance()->getTexture("board")->getSize();

	static const float layerHeight = boardSize.y / 4.f;
	static const float gapBetweenRows = 5.f;

	// Layer
	layer = t_mousePos.y / (unsigned)layerHeight;
	float heightAlongLayer = t_mousePos.y - (layer * layerHeight);

	// Row
	row = getRow(heightAlongLayer / layerHeight);

	// Col
	float minWidthScalar = 2 * cos(70.f * (3.14159 / 180.f)); // Board is rotated backwards 70 degrees
	int minWidth = (int)(boardSize.x * minWidthScalar);

	float width = minWidth + (boardSize.x - minWidth) * (heightAlongLayer / layerHeight);
	float xOffset = (boardSize.x - width) / 2.f;

	// Check if the click is within the width of the board at this height
	if (t_mousePos.x > xOffset && t_mousePos.x < xOffset + width)
		col = (uint8_t)((t_mousePos.x - xOffset) / (width / 4));

	return { layer,row,col };
}

//*****************************************************************************

uint8_t PlayerInput::getRow(float t_rowPct)
{
	// if the pct exceeds these values its in that row
	static const std::array<float, 3> rowValues{
		0.1875f, // under this is row 0, above is 1
		0.3975f, // above this is row 2
		0.6525f // above this is row 3
	};

	uint8_t row = 0;

	for (auto& a : rowValues)
		if (t_rowPct > a)
			row++;
		else
			break;

	return row;
}
