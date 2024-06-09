
namespace hi::parser
{
	class ParsingException : public std::exception
	{
	public:
		ParsingException(
			const std::string& message,
			const std::string& line = "",
			const std::string& filename = "",
			int line_number = -1
		);

		const char* what() const noexcept override;

		const std::string& getFilename() const noexcept;
		int getLineNumber() const noexcept;

	private:
		std::string _full_message;
		std::string _filename;
		int _line_number;
	}; // class ParsingException

	class Tag
	{
	public:
		using Pointer = std::shared_ptr<Tag>;

		Tag(const std::string& name);
		Tag(const std::string& name, const std::string& text);
		Tag(const std::string& name, const std::string& text, const std::string& filename, int line_number);

		void addChild(const Pointer& child);
		void addClass(const std::string& class_);
		void addAttribute(const std::string& key, const std::string& value);

		const std::string& getName() const;
		const std::string& getText() const;
		const std::string& getAttribute(const std::string& key) const;
		const std::list<std::string>& getClasses() const;
		const std::list<Pointer>& getChildren() const;

		bool hasAttribute(const std::string& key) const;
		bool hasClass(const std::string& class_) const;

	private:
		std::string _name;
		std::string _text;
		std::map<std::string, std::string> _attributes;
		std::list<std::string> _classes;
		std::list<Pointer> _children;
	}; // class Tag

	class Parser
	{
	public:
		Parser();
		Parser(const std::string& filename);

		void parse(const std::string& filename);
		void parse(const std::string& filename, const std::string& content);

		const Tag::Pointer& getRoot() const;

		std::list<Tag::Pointer> findAll(const std::string& class_val) const;

	private:
		void _parse(const std::string& content);
		void _findAllRecursive(Tag::Pointer current, const std::string& class_val, std::list<Tag::Pointer>& result);

		Tag::Pointer _root;
		std::string _filename;
	}; // class Parser
} // namespace hi::parser