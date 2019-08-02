#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
	python ==> decorator를 사용해서 tag를 달아본 예제코드
'''

class Tagify():
    def __init__(self, function):
        self.function = function

    def __call__(self, *args, **kwargs):
        tagified_p = self.tagify('p', self.function(*args, **kwargs))
        tagified_b = self.tagify('b', tagified_p)
        tagified_i = self.tagify('i', tagified_b)
        return tagified_i

    def tagify(self, tag, text):
        return "<{tag}>{text}</{tag}>".format(tag=tag, text=text)


@Tagify
def set_text(text):
    print(text)
    return text

print(set_text('python')) # <i><b><p>python</p></b></i>
