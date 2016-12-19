#include "ManaSourceSpell.h"

#include "BattleField.h"
#include "DataPacker.h"
#include "Log.h"
#include "Summoner.h"

#include "battle/RoundActionsLog.h"

ManaSourceSpell::ManaSourceSpell(ability::Type type, uint8_t level, uint8_t cooldown, uint8_t mana, int8_t mana_change, const Calculator *calculator):
	Spell(type, ability::OTHER_POSITIVE, level, cooldown, mana), calculator(calculator), mana_change(mana_change)
{}

ManaSourceSpell::~ManaSourceSpell()
{
	delete this->calculator;
}

bool ManaSourceSpell::do_apply(BattleAction::targets_t &log, combatant_ptr_t&, combatant_ptr_t &target, BattleField* field) const
{
	if (!target->is_summoner())
		throw Exception("Applying mana changing on non-summoner combatant");

	auto summoner = target->get_summoner();
	summoner->change_extra_mana(this->spell, this->mana_change);

	uint16_t value = this->calculator->get(summoner->get_health());
	field->damage(target, target, value);

	log.emplace_back(target->object_id(), DataPacker().pack(ability::Action::ATTACK, (int16_t)value));
	log.emplace_back(target->object_id(), DataPacker().pack(ability::Action::CHANGE_MANA, (int16_t)this->mana_change));

	return true;
}