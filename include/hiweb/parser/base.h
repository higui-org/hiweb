/**
 * @file base.h
 * @brief Header file defining the base classes for the HiGUI parser module.
 *
 * This file contains the class definitions for the HiGUI project's parser module.
 * It includes the definitions for ParserBase and ParsingException classes,
 * which are integral to the HiGUI parsing system. These classes provide the
 * framework for parsing and handling exceptions for HTML-like structured data,
 * facilitating the construction and manipulation of a document object model (DOM).
 *
 * @author setbe <max@lafk.eu>
 * @version 24.4
 * @date 1/4/2024
 */

#ifndef HiWEB_PARSER_BASE_H
#define HiWEB_PARSER_BASE_H

#include <memory>
#include <list>         // for Parser::findAll()
#include <string>
#include <stdexcept>    // for ParsingException's logic
 
#include "hiweb/dom.h"

namespace hi::web
{
    /**
     * @class ParserBase
     * @brief Abstract base class for parsers in the HiGUI system.
     *
     * This class provides an interface for parsing documents into a structured format
     * and managing the resulting Tag objects within a DOM. It defines the core
     * functionality required for reading documents, writing tags, finding tags, and
     * accessing the DOM. Implementations should provide specific parsing logic.
     */
    class Parser
    {
    public:
        using Pointer = std::unique_ptr<Parser>;

        Parser() noexcept = default;
        virtual ~Parser() = default;

        /**
         * @brief Reads and parses a document from the specified file.
         * @param filename The path of the file to be parsed.
         */
        virtual void read(const std::string& filename) = 0;

        /**
         * @brief Writes a new tag into a specified location within the document.
         * @param where A pointer to the tag under which the new tag will be added.
         * @param tag The tag to be added to the document.
         * @return true if the tag was successfully added, false otherwise.
         */
        bool write(const Tag::Pointer& where, const Tag& tag);

        /**
         * @brief Finds a tag by its unique ID.
         * @param id The unique ID of the tag to find.
         * @return A pointer to the found tag, or nullptr if not found.
         */
        Tag::Pointer find(const std::string& id) const;

        /**
         * @brief Finds all tags that match a given class value.
         * @param class_val The class value to match.
         * @return A list of pointers to the matching tags.
         */
        std::list<Tag::Pointer> findAll(const std::string& class_val) const;

        /**
         * @brief Gets the DOM object managed by the parser.
         * @return A reference to the DOM object.
         */
        DOM& getDOM() const noexcept { return dom; }

    private:
        mutable DOM dom; ///< The DOM for managing parsed tags, mutable for const method modifications.

        static Tag::Pointer findRecursive(Tag::Pointer current, const std::string& id);
        static void findAllRecursive(Tag::Pointer current, const std::string& class_val, std::list<Tag::Pointer>& result);
    };


    /**
     * @class ParsingException
     * @brief Exception class for handling parsing errors in the HiGUI system.
     *
     * This class encapsulates information about errors that occur during the parsing process,
     * including the file name, line number, and an error message. It extends the standard
     * exception class to provide detailed error information which can be used for debugging
     * and error reporting.
     */
    class ParsingException : public std::exception
    {
    public:
        /**
         * @brief Constructs a new ParsingException with a specified error message, file name, and line number.
         * @param message The error message describing what went wrong.
         * @param filename (Optional) The name of the file where the error occurred.
         * @param line_number (Optional) The line number in the file where the error was detected.
         */
        ParsingException(const std::string& message, const std::string& line = "", const std::string& filename = "", int line_number = -1);

        /**
         * @brief Provides the error message including file name and line number if available.
         * @return The full error message as a C-style string.
         */
        const char* what() const noexcept override;

        /**
         * @brief Gets the name of the file where the error occurred.
         * @return The file name as a standard string.
         */
        const std::string& getFilename() const noexcept;

        /**
         * @brief Gets the line number where the error was detected.
         * @return The line number.
         */
        int getLineNumber() const noexcept;

    private:
        std::string filename; ///< The name of the file where the error occurred.
        std::string line; ///< The markup line.
        int line_number; ///< The line number at which the error was detected.
        std::string full_message; ///< The full error message.
    };


} // namespace hi::parser

#endif // HiWEB_PARSER_BASE_H