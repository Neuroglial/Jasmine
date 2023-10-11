#pragma once
#include <iostream>
#include <unordered_map>

namespace Jasmine {
	class Tool {
	public:
		template <typename T>
		static T Average(const T& value, uint32_t count, uint32_t id)
		{
			static std::unordered_map<uint32_t, T> _map;
			auto& sum = _map.find(id);

			if (sum == _map.end()) {
				_map[id] = value;
				return value;
			}

			else {
				sum->second = (sum->second * count + value) / (1 + count);
				return sum->second;
				
			}
		}
	};
}