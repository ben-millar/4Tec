#include <Input.h>

bool Input::handleMouseInput(sf::Vector2i t_mousePos)
{
	if (!m_board)
		return false;

	auto input = calculateBoardPiece(t_mousePos);
	return m_board->makeMove(std::get<0>(input), std::get<1>(input), std::get<2>(input));
}

////////////////////////////////////////////////////////////

void Input::assignBoard(Board* t_board)
{
	m_board = t_board;
}

////////////////////////////////////////////////////////////

std::tuple<uint8_t, uint8_t, uint8_t> Input::calculateBoardPiece(sf::Vector2i t_mousePos)
{
	std::tuple<uint8_t, uint8_t, uint8_t> points(255, 255, 255);
	/// <summary>
	/// variable used later
	/// </summary>
	unsigned maxWidth = 720; // maximum width of the cols
	float minWidthScaler = 1.85f; // difference between max with and min width
	float level = t_mousePos.y / 200.0f; // get the level the click is on 0-3
	float rowPct = level - (int)level; // remove the level to get in range 0-1
	float xOffset = 125 - (125 * rowPct); //change the offset of the x depending on how low in the level the click is
	float width = (maxWidth - xOffset * minWidthScaler); // how wide the board is at a given y value

	std::get<0>(points) = static_cast<uint8_t>(level); // store the level as an int
	std::get<1>(points) = getRow(rowPct); // calculate the row using a function

	if (t_mousePos.x > xOffset && t_mousePos.x < xOffset + width) // check if the click is within the range width wise
		std::get<2>(points) = static_cast<uint8_t>((t_mousePos.x - xOffset) / (width / 4)); // store the info
	return points;
}

////////////////////////////////////////////////////////////

uint8_t Input::getRow(float t_levelPct)
{
	// if the pct exceeds these values its in that row
	static const std::array<float, 3> rowValues{
		0.1875f, // under this is row 0, above is 1
		0.3975f, // above this is row 2
		0.6525f // above this is row 3
	};
	uint8_t row = 0;

	for (auto& a : rowValues)
	{
		if (t_levelPct > a)
			row++;
		else
			break;
	}

	return row;
}
