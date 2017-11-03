#ifndef MACROS_H
#define MACROS_H

#define ADD_MEMBER_WITH_GETER_AND_SETTER( Name, Prefix, Type, InitValue ) \
public: \
	void Set##Name( const Type a_##Prefix##Name ) \
	{ \
		m_##Prefix##Name = a_##Prefix##Name; \
	} \
	Type Get##Name() const \
	{ \
		return m_##Prefix##Name; \
	} \
private: \
	Type m_##Prefix##Name = InitValue; \

#endif // MACROS_H
