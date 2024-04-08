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
    return findRecursive(dom.getRoot(), id);
}

std::list<Tag::Pointer> Parser::findAll(const std::string& class_val) const
{
    std::list<Tag::Pointer> result;
    findAllRecursive(dom.getRoot(), class_val, result);
    return result;
}

Tag::Pointer Parser::findRecursive(Tag::Pointer current, const std::string& id) {
    if (!current) return nullptr;

    if (current->getId() == id) return current;

    for (const auto& child : current->getChildren())
    {
        Tag::Pointer result = findRecursive(child, id);
        if (result) return result;
    }
    return nullptr;
}

void Parser::findAllRecursive(
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
        findAllRecursive(child, class_val, result);
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
    : filename(filename),
    line_number(line_number)
{
    full_message = "ParsingException was thrown";                   // "ParsingException was thrown"

    if (!filename.empty())
        full_message += " in file \"" + filename + "\"";            // " in file "<filename>""
    if (line_number >= 0)
        full_message += " on line " + std::to_string(line_number);  // " on line <line_number>"

    full_message += ":\n\t" + message;      // ":<new line><tab><message>"

    if (!line.empty())
        full_message += "\n\t\"" + line + "\"";                     // "<new line><tab>"line""
}

const char* ParsingException::what() const noexcept
{
    return full_message.c_str();
}

const std::string& ParsingException::getFilename() const noexcept
{
    return filename;
}

int ParsingException::getLineNumber() const noexcept
{
    return line_number;
}


} // namespace 'hi::parser'