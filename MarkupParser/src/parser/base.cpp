#include "hiweb/parser/base.h"

namespace hi::web
{


/*
        Parser methods
    (no getters/setters)
            |
            |
           \ /
*/
bool Parser::write(const Tag::Pointer& where, const Tag& tag) {
    if (!where) return false;

    Tag::Pointer newTag = std::make_shared<Tag>(tag);
    where->addChild(newTag);

    return true;
}

Tag::Pointer Parser::find(const std::string& id) const
{
    return _findRecursive(_dom.getRoot(), id);
}

std::list<Tag::Pointer> Parser::findAll(const std::string& class_val) const
{
    std::list<Tag::Pointer> result;
    _findAllRecursive(_dom.getRoot(), class_val, result);
    return result;
}

Tag::Pointer Parser::_findRecursive(Tag::Pointer current, const std::string& id) {
    if (!current) return nullptr;

    if (current->getId() == id) return current;

    for (const auto& child : current->getChildren())
    {
        Tag::Pointer result = _findRecursive(child, id);
        if (result) return result;
    }
    return nullptr;
}

void Parser::_findAllRecursive(
    Tag::Pointer current,
    const std::string& class_val,
    std::list<Tag::Pointer>& result) {
    if (!current) return;

    for (std::string& class_ : current->getClasses())
    {
        if (class_val == class_)
            result.push_back(current);
    }

    for (const auto& child : current->getChildren())
    {
        _findAllRecursive(child, class_val, result);
    }
}


/*

    class ParsingException
*/
ParsingException::ParsingException(
    const std::string& message,
    const std::string& line,
    const std::string& filename,
    int line_number
)
    : _filename(filename),
    _line_number(line_number)
{
    _full_message = "ParsingException was thrown";                   // "ParsingException was thrown"

    if (!filename.empty())
        _full_message += " in file \"" + filename + "\"";            // " in file "<filename>""
    if (line_number >= 0)
        _full_message += " on line " + std::to_string(line_number);  // " on line <line_number>"

    _full_message += ":\n\t" + message;      // ":<new line><tab><message>"

    if (!line.empty())
        _full_message += "\n\t\"" + line + "\"";                     // "<new line><tab>"line""
}

const char* ParsingException::what() const noexcept
{
    return _full_message.c_str();
}

const std::string& ParsingException::getFilename() const noexcept
{
    return _filename;
}

int ParsingException::getLineNumber() const noexcept
{
    return _line_number;
}


} // namespace 'hi::parser'