#pragma once

#include <optional>
#include <unordered_map>
#include <variant>
#include <vector>
#include "constraint.h"
#include "forces.h"
#include "object.h"

using Force = std::optional<std::variant<GravF, DragF, SpringF, Gravity>>;
using Constraint = std::optional<std::variant<DistanceC>>;
using SystemF = std::unordered_map<Mass*, std::vector<Force>>;
using SystemC = std::unordered_map<Mass*, std::vector<Constraint>>;
