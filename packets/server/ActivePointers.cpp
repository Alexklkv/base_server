#include "ActivePointers.h"
#include "Pointers.h"

namespace server
{
//устанавливаем позиции начала и конца для указателей, которые необходимо передать клиенту для отображения
constexpr uint32_t  POINT_BEGIN = PointerID::POINTER_SHOP_ITEMS;
constexpr uint32_t  POINT_END	= PointerID::POINTER_SHOP_CARDS;
	
SERVER_PACKET_SOURCE(ActivePointers)

ActivePointers::ActivePointers(Pointers* pointers)
{
	for(uint32_t i = POINT_BEGIN; i <= POINT_END; ++i)
	{
		this->add(i);
		this->add(static_cast<uint8_t>(pointers->get(Enum<PointerID>::wrap(i))));
	}
	this->write();
}

}