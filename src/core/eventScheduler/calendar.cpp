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

#include "calendar.h"
#include "core/simulation/Simulation.h"

Calendar::Calendar()
{
	m_Events = new Events;
}

Calendar::~Calendar()
{
	delete m_Events;
}

void Calendar::InsertEvent (Event *newEvent) const
{
	if (IsEmpty ())
    {
		m_Events->push_front(newEvent);
		return;
    }

	for (auto iter = m_Events->begin(); iter != m_Events->end(); ++iter)
	{
		Event* event = *iter;
		if(newEvent->GetTimeStamp() < event->GetTimeStamp())
		{
			m_Events->insert(iter, newEvent);
			return;
		}
	}

	m_Events->push_back(newEvent);;
}

bool Calendar::IsEmpty() const
{
	return m_Events->empty();
}

Event* Calendar::GetEvent() const
{
	if (IsEmpty ())
		return nullptr;

	Event *event = m_Events->front();
	return event;
}

void Calendar::RemoveEvent() const
{
	if (!IsEmpty ())
	{
		Event *event = m_Events->front();
		m_Events->pop_front();
		delete event;
	}
}

void Calendar::Schedule(double time, Event* event) const
{
	event->SetTimeStamp(time + Simulation::Get().Now());
	InsertEvent(event);
}
