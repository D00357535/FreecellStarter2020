#include "pch.h"
#include "Cell.h"
#include "WindowsCards.h"

Cell::Cell(int left, int top, int right, int bottom)
{
	mLeft = left;
	mTop = top;
	mRight = right;
	mBottom = bottom;
	mSelected = false;
	mCheat = false;
}
void Cell::AddCard(int index)
{
	mCards.push_back(index);
}
int Cell::RemoveCard()
{
	int top = GetTopCard();
	mCards.pop_back();
	return top;
}
void Cell::SelectCell(bool s)
{
	mSelected = s;
}
void Cell::ToggleCheat(bool onoff) {
	mCheat = onoff;
}
int Cell::GetTopCard()
{
	return mCards.back();
}
void Cell::Draw(CDC& dc)
{
	dc.Rectangle(mLeft, mTop, mRight, mBottom);
	for (unsigned int i = 0; i < mCards.size(); i++)
	{
		DrawCard(dc, mLeft + CELL_MARGIN, mTop + CELL_MARGIN + CARD_STAGGER * i, mCards[i], mSelected);
	}
}
bool Cell::IsClicked(int x, int y)
{
	if (x >= mLeft && x <= mRight && y >= mTop && y <= mBottom)
		return true;
	else
		return false;
}

bool Cell::CanRemoveCard() {
	if (mCards.size() >= 1)
		return true;
	else
		return false;
}

void Cell::EmptyCell() {
	mCards.resize(0);
}
bool EndCell::CanRemoveCard() {
	return false;
}
bool StartCell::CanAddCard(int index) {
	if (mCards.size() == 0) {
		return true;
	}
	int topcard = GetTopCard();
	int tcsuit = topcard % 4;
	int suit = index % 4;

	if (mCheat == true) {
			if (topcard / 4 > (index / 4) ) {
				if (suit == tcsuit) {
					return true;
				}
				if (suit == 0 && tcsuit == 3) {
					return true;
				}
				if (suit == 1 && tcsuit == 2) {
					return true;
				}
				if (suit == 2 && tcsuit == 1) {
					return true;
				}
				if (suit == 3 && tcsuit == 0) {
					return true;
				}
			}
			return false;
	}

	if (tcsuit != suit) {
		if (topcard / 4 == (index / 4) + 1) {
			if (suit == 0 && tcsuit != 3) {
				return true;
			}
			if (suit == 1 && tcsuit != 2) {
				return true;
			}
			if (suit == 2 && tcsuit != 1) {
				return true;
			}
			if (suit == 3 && tcsuit != 0) {
				return true;
			}
		}
	}
	return false;
}
bool EndCell::CanAddCard(int index) {
	if (mCards.size() == 0 ) {
		if (index / 4 == 0) {
			return true;
		}
		return false;
	}
	if (GetTopCard() / 4 == (index / 4) - 1 && index%4 ==GetTopCard()%4) {
		return true;
	}
	return false;
}
bool FreeCell::CanAddCard(int index) {
	if (mCards.size() == 0) {
		return true;
	}
	return false;
}
void EndCell::Draw(CDC& dc)
{
	dc.Rectangle(mLeft, mTop, mRight, mBottom);
	for (unsigned int i = 0; i < mCards.size(); i++)
	{
		DrawCard(dc, mLeft + CELL_MARGIN, mTop + CELL_MARGIN, mCards[i], mSelected);
	}
}