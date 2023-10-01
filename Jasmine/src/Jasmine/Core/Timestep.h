#pragma once

namespace Jasmine {

	class Timestep
	{
	public:
		Timestep(float time = 0.0f)
			: m_Time(time)
		{
		}

		operator float() const { return m_Time; }

		float GetSeconds() const { return m_Time; }
		float GetMilliseconds() const { return m_Time * 1000.0f; }
		double GetLifeTimeSeconds() const { return m_LifeTime; }
		double GetLifeTimeMilliseconds() const { return m_LifeTime * 1000.0; }

		static Timestep UpdateLifeTime(double time) {
			static double LastTime;
			LastTime = m_LifeTime;
			m_LifeTime = time;
			return Timestep(m_LifeTime - LastTime);
		}

	private:
		float m_Time;
		inline static double m_LifeTime = 0.0;
	};

}