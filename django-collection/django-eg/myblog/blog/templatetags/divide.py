from django import template

register = template.Library()

@register.filter(name = 'divide')
def divide(v1, v2):
	v1 = min(v1, v2)
	return (v1//v2)*100
