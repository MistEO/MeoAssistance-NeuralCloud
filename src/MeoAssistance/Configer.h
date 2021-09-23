﻿#pragma once

#include "AbstractConfiger.h"

#include <string>
#include <unordered_map>
#include <memory>

#include "AsstDef.h"

namespace asst {
	class Configer : public AbstractConfiger
	{
	public:
		virtual ~Configer() = default;

		static Configer& get_instance() {
			static Configer unique_instance;
			return unique_instance;
		}

		constexpr static int WindowWidthDefault = 1280;
		constexpr static int WindowHeightDefault = 720;
		constexpr static double TemplThresholdDefault = 0.9;
		constexpr static double HistThresholdDefault = 0.9;

		std::string m_version;
		Options m_options;
		std::unordered_map<std::string, EmulatorInfo> m_handles;

	protected:
		Configer() = default;
		Configer(const Configer& rhs) = default;
		Configer(Configer&& rhs) noexcept = default;

		Configer& operator=(const Configer& rhs) = default;
		Configer& operator=(Configer&& rhs) noexcept = default;

		virtual bool parse(const json::value& json) override;
	};
}
