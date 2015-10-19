#include <cstdlib>
#include <string>

class RoomDescription {

	// Total possible rooms: 5 x 3 x 3 x 3 = 135
	enum RoomSize { xSmall, Small, Medium, Large, xLarge };
	enum RoomClean { Clean, sDirty, Dirty };
	enum RoomLayout { Table, Bed, Empty };
	enum RoomLight { Candle, Torch, FirePlace };

	public : static std::string ToString() {
		// It is a small clean room with a table and four chairs in it. The room is lit by a fireplace.
		return "Room Description: It is a " + getRoomSize() + " " + getRoomClean() + " " + getRoomLayout() + " The room is lit by a " + getRoomLight() + ".";
	}

	static std::string getRoomSize() {
		RoomSize s = RoomSize(rand() % RoomSize::xLarge);
		switch (s) {
			case xSmall:	return "really small";
			case Small:		return "small";
			case Medium:	return "medium";
			case Large:		return "large";
			case xLarge:	return "really large";
			default:		return "";
		}
	}

	static std::string getRoomClean() {
		RoomClean s = RoomClean(rand() % RoomClean::Dirty);
		switch (s) {
			case Clean:		return "clean";
			case sDirty:	return "semi-dirty";
			case Dirty:		return "medium";
			default:		return "";
		}
	}

	static std::string getRoomLayout() {
		RoomLayout s = RoomLayout(rand() % RoomLayout::Empty);
		switch (s) {
			case Table:		return "room with a table and four chairs in it.";
			case Bed:		return "room with a bed in the corner.";
			case Empty:		return "empty room.";
			default:		return "";
		}
	}

	static std::string getRoomLight() {
		RoomLight s = RoomLight(rand() % RoomLight::FirePlace);
		switch (s) {
			case Candle:	return "candle";
			case Torch:		return "torch";
			case FirePlace:	return "fireplace";
			default:		return "";
		}
	}

};