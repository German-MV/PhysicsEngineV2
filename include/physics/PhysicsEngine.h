#pragma once

#include <vector>

#include "utils.h"
#include "physics/Object.h"
#include "physics/Force.h"
#include "physics/ApplicationPoint.h"
#include "physics/Constraint.h"
#include "physics/System.h"

START_PHYSICS_NAMESPACE

class PhysicsEngine
{
protected:
	using PtrObj = std::shared_ptr<Object>;
	using PtrFrc = std::shared_ptr<Force>;
	using PtrApp = std::shared_ptr<ApplicationPoint>;
	using PtrCst = std::shared_ptr<Constraint>;

public:
	template <typename T>
	std::shared_ptr<T> addExisting(const std::shared_ptr<T>& ptr)
	{
		if constexpr (std::is_base_of<Object, T>::value)
		{
			objects.push_back(ptr);
			return ptr;
		}
		else if constexpr (std::is_base_of<Force, T>::value)
		{
			forces.push_back(ptr);
			return ptr;
		}
		else if constexpr (std::is_base_of<ApplicationPoint, T>::value)
		{
			appPoints.push_back(ptr);
			return ptr;
		}
		else if constexpr (std::is_base_of<Constraint, T>::value)
		{
			constraints.push_back(ptr);
			return ptr;
		}
		else if constexpr (std::is_base_of<System, T>::value)
		{
			std::dynamic_pointer_cast<System>(ptr)->addToEngine(*this);
			return ptr;
		}
		else
		{
			static_assert(always_false<T>::value, "T debe derivar de Object, Force, ApplicationPoint o Constraint.");
			return nullptr;
		}
	}

	template <typename T, typename... Args>
	std::shared_ptr<T> add(Args&&... args)
	{
		if constexpr (std::is_base_of<Object, T>::value)
		{
			auto ptr = std::make_shared<T>(std::forward<Args>(args)...);
			objects.push_back(ptr);
			return ptr;
		}
		else if constexpr (std::is_base_of<Force, T>::value)
		{
			auto ptr = std::make_shared<T>(std::forward<Args>(args)...);
			forces.push_back(ptr);
			return ptr;
		}
		else if constexpr (std::is_base_of<ApplicationPoint, T>::value)
		{
			auto ptr = std::make_shared<T>(std::forward<Args>(args)...);
			appPoints.push_back(ptr);
			return ptr;
		}
		else if constexpr (std::is_base_of<Constraint, T>::value)
		{
			auto ptr = std::make_shared<T>(std::forward<Args>(args)...);
			constraints.push_back(ptr);
			return ptr;
		}
		else if constexpr (std::is_base_of<System, T>::value)
		{
			auto ptr = std::make_shared<T>(std::forward<Args>(args)...);
			std::dynamic_pointer_cast<System>(ptr)->addToEngine(*this);
			return ptr;
		}
		else
		{
			static_assert(always_false<T>::value, "Type T must derive from Object, Interaction, ApplicationPoint, or Constraint.");
			return nullptr;
		}
	}

	template <typename T>
	void remove(const std::shared_ptr<T>& ptr)
	{
		if constexpr (std::is_base_of<Object, T>::value)
		{
			objects.erase(std::remove(objects.begin(), objects.end(), ptr), objects.end());
		}
		else if constexpr (std::is_base_of<Force, T>::value)
		{
			forces.erase(std::remove(forces.begin(), forces.end(), ptr), forces.end());
		}
		else if constexpr (std::is_base_of<ApplicationPoint, T>::value)
		{
			appPoints.erase(std::remove(appPoints.begin(), appPoints.end(), ptr), appPoints.end());
		}
		else if constexpr (std::is_base_of<Constraint, T>::value)
		{
			constraints.erase(std::remove(constraints.begin(), constraints.end(), ptr), constraints.end());
		}
		else if constexpr (std::is_base_of<System, T>::value)
		{
			std::dynamic_pointer_cast<System>(ptr)->removeFromEngine(*this);
		}
		else
		{
			static_assert(always_false<T>::value, "Type T must derive from Object, Interaction, ApplicationPoint, or Constraint.");
		}
	}

	void update(float deltaTime, const unsigned int nSubsteps = 6, const unsigned int nSolverIterations = 6);

	template <typename T>
	std::vector<std::shared_ptr<T>> getEvery()
	{
		static_assert(always_false<T>::value, "Specialization of getEvery<T> not implemented for this type T.");
		return {};
	}
	
	template<>
	std::vector<PtrObj> getEvery();

	template<>
	std::vector<PtrFrc> getEvery();

	template<>
	std::vector<PtrApp> getEvery();

	template<>
	std::vector<PtrCst> getEvery();

protected:
	std::vector<PtrObj> objects;
	std::vector<PtrFrc> forces;
	std::vector<PtrApp> appPoints;
	std::vector<PtrCst> constraints;
};

END_PHYSICS_NAMESPACE