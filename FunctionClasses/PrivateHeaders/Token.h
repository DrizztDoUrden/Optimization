#pragma once
#include <string>



using namespace std;



namespace Optimization
{
	namespace FunctionClasses
	{
		class Token
		{
			int _id;
			size_t _position;

		public:
			Token(int id, size_t position);

			__inline int GetId() const { return _id; }
			__inline size_t GetPosition() const { return _position; }
		};

		template<typename TValue, int id>
		class ValuedToken : public Token
		{
			TValue _value;

		public:
			ValuedToken(TValue value, size_t position)
				: Token(id, position)
				, _value(value)
			{
				
			}

			__inline TValue GetValue() const { return _value; }
		};

		enum class TokenIds
		{
			Number = -1,
			Double = -2,
			Variable = -3,
			Operator = -4,
		};

		enum class Operators
		{
			Sin,
			Cos,
			Log,
			Exp,
		};

		using Number = ValuedToken<int, (int)TokenIds::Number>;
		using RealNumber = ValuedToken<double, (int)TokenIds::Double>;
		using Variable = ValuedToken<int, (int)TokenIds::Variable>;
		using Operator = ValuedToken<Operators, (int)TokenIds::Operator>;
	}
}
