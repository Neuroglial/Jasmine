#pragma once
#include "JM_PCH.h"

#include "glm/glm.hpp"
#include "Jasmine/Core/Timestep.h"
#include "Jasmine/Renderer/Renderer2D.h"
#include <omp.h>

namespace Jasmine {
	class Particle
	{
	protected:
		glm::vec2 position;
		bool destory = false;

		inline void Destory() { destory = true; }
	public:
		Particle(glm::vec2 position) :position(position) {
		};

		inline bool ShouledDestory() { return destory; }
		virtual float GetLifeTime() = 0;
		virtual void OnUpdate(Jasmine::Timestep ts) = 0;
		virtual void Draw(float z) = 0;
	};

	class Emitter
	{
	private:
		glm::vec3 LastPos;
	protected:
		glm::vec3 position;
		std::vector<Particle*> pts;
		uint32_t MaxParticlesSize;
		uint32_t ptsTail = 0;
		uint32_t ptsCount = 0;

		bool smoothMove = true;

		template <typename T>
		void EitterParticles(Timestep ts, float rate) {

			static float accumulate = 0.0f;
			accumulate += rate * ts.GetSeconds();
			float Count;
			accumulate = modff(accumulate, &Count);

			for (float i = 0; i < Count; i++) {
				float factor = i / Count;
				glm::vec3 tpos;

				if (smoothMove)
					tpos = LastPos * (1.0f - factor) + position * factor;
				else
					tpos = position;

				auto p = new T(tpos);

				pts[(ptsTail + ptsCount++) % pts.size()] = p;
			}
			LastPos = position;
		}

		void ParticlesUpdate(Timestep ts) {
			while (pts[ptsTail] && pts[ptsTail]->ShouledDestory()) {
				delete pts[ptsTail];
				pts[ptsTail] = nullptr;
				ptsTail = ++ptsTail % pts.size();
				ptsCount--;
			}

			JM_ASSERT(ptsCount <= pts.size(), "Particles is too much.");

#pragma omp parallel
			{
				int id = omp_get_thread_num();
				int numthreads = omp_get_num_threads();

				for (int i = id; i < ptsCount; i += numthreads) {
					int j = (ptsTail + i) % pts.size();
					pts[j]->OnUpdate(ts);
				}
			}
		}

	public:
		uint32_t GetParticlesCount() {
			return ptsCount;
		}

		Emitter(glm::vec3 position, uint32_t MaxParticlesSize = 200) :LastPos(position),position(position), MaxParticlesSize(MaxParticlesSize) {
			pts.resize(MaxParticlesSize);
		};

		void SetSmoothMove(bool enable) { smoothMove = enable; }

		virtual void OnUpdate(Timestep ts) = 0;
		void OnDraw() {
			float Front = position.z;
			for (int i = 0; i < ptsCount; i++) {
				auto j = (i + ptsTail) % pts.size();
				pts[j]->Draw(Front += 0.0000001f);
			}
		}
	};
}