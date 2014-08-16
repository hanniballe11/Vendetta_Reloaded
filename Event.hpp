/*n
 * Event.h
 *
 *  Created on: 6 juil. 2012
 *      Author: Erwann
 */

#ifndef EVENT_H_
#define EVENT_H_

enum eventType{
	Moved,
	Attack,
	Follow,
	Attacked,
	Followed,
	Fire,
	Dash,
	HealthGain,
	HealthLost,
	HealthCritical,
	ManaGain,
	ManaLost,
	NeedMana,
	StaminaGain,
	StaminaLost,
	NeedStamina,
	StateChanged,
	Working,
	Summoned,
	Summoning,
	Die,
	Revive
	};

#endif /* EVENT_H_ */