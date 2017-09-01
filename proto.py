class Context():
    def __init__(self):
        self.string_or_none = None
        self.list_or_none = None
    def __init__(self, something):
        if isinstance(something, basestring):
            self.string_or_none = something
            self.list_or_none = None
	elif isinstance(something, list):
            self.string_or_none = None
            self.list_or_none = something
    def __div__(self, splitter):
        if self.string_or_none != None:
            return Context(self.string_or_none.split(splitter))
    def __mod__(self, joiner):
        if self.list_or_none != None:
            return Context(joiner.join(self.list_or_none))
    def __str__(self):
        return self.string_or_none


if __name__ == '__main__':
	print Context("12345")/'3'%'-'
