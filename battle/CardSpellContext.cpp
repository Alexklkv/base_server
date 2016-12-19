#include "CardSpellContext.h"

#include "ability/spells/Spell.h"

CardSpellContext::CardSpellContext(BattleField *field, combatant_ptr_t &caster, combatant_ptr_t &target, const Spell *spell):
	CardActionContext(field), spell(spell), caster(caster->get_summoner()), cooldown(spell->cooldown), mana(spell->mana)
{
	this->targets = spell->targets(caster, target, field);
}