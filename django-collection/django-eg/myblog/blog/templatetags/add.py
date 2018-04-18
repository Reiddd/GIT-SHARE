from django import template

register = template.Library()

@register.filter(name = 'add')
def add(v1, v2):
	return v1+v2
