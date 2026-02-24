#pragma once

#include <optional>
#include <unordered_map>
#include <variant>
#include <vector>
#include "forces.h"
#include "object.h"

using Force = std::optional<std::variant<GravF, DragF, SpringF>>;
using Forces = std::vector<Force>;
using System = std::unordered_map<Object*, Forces>;
