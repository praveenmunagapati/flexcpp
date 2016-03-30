// Generated by Bisonc++ V5.00.00 on Wed, 30 Mar 2016 11:49:33 +0200

#ifndef ParserBase_h_included
#define ParserBase_h_included

#include <exception>
#include <vector>
#include <iostream>

// $insert preincludes
#include "preinclude.h"
// $insert debugincludes
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <iomanip>

namespace // anonymous
{
    struct PI__;
}


// $insert polymorphic
enum class Tag__
{
    VECTOR,
    TEXTTYPE,
    PATTERN,
    STRING,
    INTERVAL,
    CHARCLASS,
};

namespace Meta__
{

template <Tag__ tag>
struct TypeOf;

template <typename Tp_>
struct TagOf;

// $insert polymorphicSpecializations
enum { sizeofTag__ = 6 };

extern char const *idOfTag__[];
template <>
struct TagOf<std::vector<std::string>>
{
    static Tag__ const tag = Tag__::VECTOR;
};

template <>
struct TagOf<FlexTypes::TextType>
{
    static Tag__ const tag = Tag__::TEXTTYPE;
};

template <>
struct TagOf<Pattern>
{
    static Tag__ const tag = Tag__::PATTERN;
};

template <>
struct TagOf<std::string>
{
    static Tag__ const tag = Tag__::STRING;
};

template <>
struct TagOf<Interval>
{
    static Tag__ const tag = Tag__::INTERVAL;
};

template <>
struct TagOf<CharClass>
{
    static Tag__ const tag = Tag__::CHARCLASS;
};

template <>
struct TypeOf<Tag__::VECTOR>
{
    typedef std::vector<std::string> type;
};

template <>
struct TypeOf<Tag__::TEXTTYPE>
{
    typedef FlexTypes::TextType type;
};

template <>
struct TypeOf<Tag__::PATTERN>
{
    typedef Pattern type;
};

template <>
struct TypeOf<Tag__::STRING>
{
    typedef std::string type;
};

template <>
struct TypeOf<Tag__::INTERVAL>
{
    typedef Interval type;
};

template <>
struct TypeOf<Tag__::CHARCLASS>
{
    typedef CharClass type;
};

    // The Base class: 
    // Individual semantic value classes are derived from this class.
    // This class offers a member returning the value's Tag__,
    // a member cloning the object of its derived Semantic<Tag__> 
    // and a member returning a pointerr to its derived Semantic<Tag__> 
    // data, used by SType. Since SType's user knows what data type 
    // he/she looks at, the user can do a static cast to that type.
    // See also Bisonc++'s distribution file README.polymorphic-techical
class Base
{
    protected:

        Tag__ d_baseTag;    // Base should not be used for Tag__ values
                            // outside of the enum class Tag__ range.

            // these members implement polymorphism without using
            // virtual functions. 
        Base *(*d_baseClone)(Base const *thisObj) = defaultClone;
        void *(*d_baseData)(Base const *thisObj) = noData;

    public:
        Base();

        Base(Base const &other) = delete;

        Tag__ tag() const;
        Base *clone() const;
        void *data() const;        

    private:
        static void *noData(Base const *thisObj);
        static Base *defaultClone(Base const *obj);
};

    // The class Semantic is derived from Base. It stores a particular
    // semantic value type. 
template <Tag__ tg_>
class Semantic: public Base
{
    typename TypeOf<tg_>::type d_data;
    
    public:
        Semantic();
        Semantic(Semantic<tg_> const &other);

            // The constructor member template forwards its arguments to
            // d_data, allowing it to be initialized using whatever
            // constructor is available for DataType
        template <typename ...Params>
        Semantic(Params &&...params);

    private:
        static Base *clone(Base const *obj);
        static void *data(Base const *obj);
};

    // The class SType wraps a pointer to Base.  It becomes the polymorphic
    // STYPE__ type It also defines a get member, allowing constructions like
    // $$.get<INT> to be used.  Instantiations of its operator= member
    // template are used to assign semantic values to the SType object.
class SType
{
    Base *d_base;

    public:
        SType();
        SType(SType const &other);
        SType(SType &&tmp);

        ~SType();

            // Specific overloads are needed for SType = SType assignments
        SType &operator=(SType const &rhs);
        SType &operator=(SType &&tmp);

            // A template member operator= is used because it allows
            // the compiler to deduce the appropriate typename
        template <typename Type>
        SType &operator=(Type const &value);

        bool valid() const;

        operator SType &()
        {
            return *this;
        }

        operator SType const &()
        {
            return *this;
        }

        template <typename Type>
        operator Type &();

        template <typename Type>
        operator Type const &();

        Tag__ tag() const;

            // this get()-member checks for invalid Semantic data and
            // (when initialized) for tags matching the tag of the stored
            // semantic value, or if the tag specified with get() does not
            // match the tag that's currently stored, then SType is
            // initialized to a default value of the type matching
            // 'tag'. If no default constructor for that type exists a
            // runtime error exception results. The option or directive 
            // warn-tag-mismatch can be specified to generate run-time 
            // warnings about tag mismatches to cerr.
        template <Tag__ tag>
        typename TypeOf<tag>::type &get();

        template <Tag__ tag, typename ...Args>
        void assign(Args &&...args);
    
        void swap(SType &other);
};

inline Base::Base()
:
    d_baseTag(static_cast<Tag__>(sizeofTag__))
{}

inline Tag__ Base::tag() const
{
    return d_baseTag;
}

inline Base *Base::clone() const
{
    return d_baseClone(this);
}

inline void *Base::data() const
{
    return d_baseData(this);
}

inline void *Base::noData(Base const *obj)              // static
{
    std::runtime_error("Default STYPE__ has no value");
    return 0;
}

inline Base *Base::defaultClone(Base const *obj)        // static
{
    return new Base;
}

template <Tag__ tg_>
Semantic<tg_>::Semantic()
{
        // Setting Base's data members:
    d_baseTag = tg_;
    d_baseClone = clone;
    d_baseData =  data;
}

template <Tag__ tg_>
Semantic<tg_>::Semantic(Semantic<tg_> const &other)
:
    d_data(other.d_data)
{
        // Setting Base's data members:
    d_baseTag = other.d_baseTag;
    d_baseClone = other.d_baseClone;
    d_baseData =  other.d_baseData;
}

template <Tag__ tg_>
template <typename ...Params>
Semantic<tg_>::Semantic(Params &&...params)
:
    d_data(std::forward<Params>(params) ...)
{
        // Setting Base's data members:
    d_baseTag = tg_;
    d_baseClone = clone;
    d_baseData =  data;
}

inline Tag__ SType::tag() const
{
    return d_base->tag();
}

inline bool SType::valid() const
{
    return tag() != static_cast<Tag__>(sizeofTag__);
}

template <typename Type>
inline SType::operator Type &()
{
    return get<TagOf<Type>::tag>();
}

template <typename Type>
inline SType::operator Type const &()
{
    return get<TagOf<Type>::tag>();
}

template <Tag__ tag, typename ...Args>
void SType::assign(Args &&...args)
{
    Semantic<tag> *semPtr = new Semantic<tag>(std::forward<Args>(args) ...);
    delete d_base;
    d_base = semPtr;
}

template <Tag__ tg>
typename TypeOf<tg>::type &SType::get()
{
// $insert warnTagMismatches

    if (tag() != tg)
    {
        std::cerr << "[Fatal] calling `.get<Tag__::" << 
            idOfTag__[static_cast<int>(tg)] << 
            ">()', but Tag " <<
            idOfTag__[static_cast<int>(tag())] << " is available. "
            " Try option --rule-numbers\n";
        throw 1;        // ABORTs
    }
    
    return *static_cast<typename TypeOf<tg>::type *>(d_base->data());
}

inline SType::SType()
:
    d_base(new Base)        // default Base object doesn't do anyting
{}                          // but prevents tests for d_base == 0

inline SType::SType(SType const &other)
:
    d_base(other.d_base->clone())
{}

inline SType::SType(SType &&tmp)
:
    d_base(tmp.d_base)
{
    tmp.d_base = 0;
}

inline SType::~SType()
{
    delete d_base;
}

inline SType &SType::operator=(SType &&tmp)
{
    swap(tmp);
    return *this;
}

    // A template assignment function is used because it allows
    // the compiler to deduce the appropriate typename
template <typename Type>
inline SType &SType::operator=(Type const &value)
{
    assign< TagOf<Type>::tag >(value);
    return *this;
}

template <Tag__ tg_>
inline Base *Semantic<tg_>::clone(Base const *obj) // static
{
    return new Semantic<tg_>{*static_cast<Semantic<tg_> const *>(obj)};
}

template <Tag__ tg_>
inline void *Semantic<tg_>::data(Base const *obj) // static
{
    return &static_cast<Semantic<tg_> *>(const_cast<Base *>(obj))->d_data;
}

}  // namespace Meta__

class ParserBase
{
    public:
// $insert tokens

    // Symbolic tokens:
    enum Tokens__
    {
        EXCL_START_CONDITION = 257,
        INCL_START_CONDITION,
        SECTION_DELIMITER,
        BASECLASSHEADER,
        CASEINSENSITIVE,
        CLASSHEADER,
        CLASSNAME,
        DEBUG,
        FILENAMES,
        IMPLEMENTATIONHEADER,
        INPUTIMPLEMENTATION,
        INPUTINTERFACE,
        INTERACTIVE,
        LEXFUNCTIONNAME,
        LEXSOURCE,
        NAMESPACE,
        NOLINES,
        PRINT,
        SKELETON_DIRECTORY,
        TARGET_DIRECTORY,
        BLOCK,
        IDENTIFIER,
        EOF_PATTERN,
        RAWSTRING,
        STRING,
        QUOTES,
        DECIMAL,
        DOLLAR,
        ESCAPE_SEQUENCE,
        CC_START,
        CC_NEGATED,
        PREDEFINED_CLASS,
        ORNL,
        CHAR,
        CC_PLUS,
        CC_MINUS,
    };

// $insert STYPE
    typedef Meta__::SType STYPE__;


    private:
        int d_stackIdx__;
        std::vector<size_t>   d_stateStack__;
        std::vector<STYPE__>  d_valueStack__;

    protected:
        enum Return__
        {
            PARSE_ACCEPT__ = 0,   // values used as parse()'s return values
            PARSE_ABORT__  = 1
        };
        enum ErrorRecovery__
        {
            DEFAULT_RECOVERY_MODE__,
            UNEXPECTED_TOKEN__,
        };
        bool        d_debug__;
        size_t      d_nErrors__;
        size_t      d_requiredTokens__;
        size_t      d_acceptedTokens__;
        int         d_token__;
        int         d_nextToken__;
        size_t      d_state__;
        STYPE__    *d_vsp__;
        STYPE__     d_val__;
        STYPE__     d_nextVal__;

        ParserBase();

// $insert debugdecl
        static std::ostringstream s_out__;
        
        std::string symbol__(int value) const;
        std::string stype__(char const *pre, STYPE__ const &semVal,
                            char const *post = "") const;
        static std::ostream &dflush__(std::ostream &out);
        void ABORT() const;
        void ACCEPT() const;
        void ERROR() const;
        void clearin();
        bool debug() const;
        void pop__(size_t count = 1);
        void push__(size_t nextState);
        void popToken__();
        void pushToken__(int token);
        void reduce__(PI__ const &productionInfo);
        void errorVerbose__();
        size_t top__() const;

    public:
        void setDebug(bool mode);
}; 

inline bool ParserBase::debug() const
{
    return d_debug__;
}

inline void ParserBase::setDebug(bool mode)
{
    d_debug__ = mode;
}

inline void ParserBase::ABORT() const
{
    // $insert debug
    if (d_debug__)
        s_out__ <<  "ABORT(): Parsing unsuccessful" << "\n" << dflush__;
    throw PARSE_ABORT__;
}

inline void ParserBase::ACCEPT() const
{
    // $insert debug
    if (d_debug__)
        s_out__ <<  "ACCEPT(): Parsing successful" << "\n" << dflush__;
    throw PARSE_ACCEPT__;
}

inline void ParserBase::ERROR() const
{
    // $insert debug
    if (d_debug__)
        s_out__ <<  "ERROR(): Forced error condition" << "\n" << dflush__;
    throw UNEXPECTED_TOKEN__;
}

// For convenience, when including ParserBase.h its symbols are available as
// symbols in the class Parser, too.
#define Parser ParserBase


#endif


