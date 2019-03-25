/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2010,2011,2012,2013 TELEMATICS LAB, Politecnico di Bari
 *
 * This file is part of LTE-Sim
 *
 * LTE-Sim is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation;
 *
 * LTE-Sim is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with LTE-Sim; if not, see <http://www.gnu.org/licenses/>.
 *
 * Author: Giuseppe Piro <g.piro@poliba.it>
 */

#ifndef CALENDAR_H_
#define CALENDAR_H_

#include "core/Core.h"
#include "make-event.h"
#include "event.h"
#include <list>

class LTE_SIM_API Calendar {
public:
	Calendar();
	virtual ~Calendar();

    typedef std::list<Event*> Events;

	bool IsEmpty() const;
	Event* GetEvent() const;
	void RemoveEvent() const;

	void Schedule(double time, Event *event) const;

	template <typename MEM, typename OBJ>
	void Schedule(double time, MEM mem_ptr, OBJ obj);

	template <typename MEM, typename OBJ, typename T1>
	void Schedule(double time, MEM mem_ptr, OBJ obj, T1 a1);

	template <typename MEM, typename OBJ, typename T1, typename T2>
	void Schedule(double time, MEM mem_ptr, OBJ obj, T1 a1, T2 a2);

	template <typename MEM, typename OBJ, typename T1, typename T2, typename T3>
	void Schedule(double time, MEM mem_ptr, OBJ obj, T1 a1, T2 a2, T3 a3);

	template <typename U1, typename T1>
	void Schedule(double time, void(*f) (U1), T1 a1);

private:
    Events *m_Events;

	void InsertEvent(Event *newEvent) const;
};

template <typename MEM, typename OBJ>
void Calendar::Schedule(double time, MEM mem_ptr, OBJ obj)
{
	Schedule(time, MakeEvent(mem_ptr, obj));
}

template <typename MEM, typename OBJ, typename T1>
void Calendar::Schedule(double time, MEM mem_ptr, OBJ obj, T1 a1)
{
	Schedule(time, MakeEvent(mem_ptr, obj, a1));
}

template <typename MEM, typename OBJ, typename T1, typename T2>
void Calendar::Schedule(double time, MEM mem_ptr, OBJ obj, T1 a1, T2 a2)
{
	Schedule(time, MakeEvent(mem_ptr, obj, a1, a2));
}

template <typename MEM, typename OBJ, typename T1, typename T2, typename T3>
void Calendar::Schedule(double time, MEM mem_ptr, OBJ obj, T1 a1, T2 a2, T3 a3)
{
	Schedule(time, MakeEvent(mem_ptr, obj, a1, a2, a3));
}

template <typename U1, typename T1>
void Calendar::Schedule(double time, void(*f) (U1), T1 a1)
{
	DoSchedule(time, MakeEvent(f, a1));
}

#endif /* CALENDAR_H_ */
