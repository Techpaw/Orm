#pragma once

namespace Orm {
  enum class Type { BOOLEAN = 0, INTEGER, STRING };
  enum class ConditionType { AND = 0, OR };
  enum class JoinType { INNER = 0, LEFT };
  enum class OrderType { ASC = 0, DESC };
}