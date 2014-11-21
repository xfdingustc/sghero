function HeroAttack(attacker, defender)
	
	local delay = attacker:attackHero(defender);
	defender:attacked();

	return delay;
	
	
end