# Create your views here.

from django.http  import HttpResponse, HttpResponseRedirect
from django.shortcuts import render, get_object_or_404, get_list_or_404
from django.urls import reverse
from .models import Question


def index(request):
	latest_question_list = Question.objects.order_by('-pub_date')[:5]
	context = {
		'latest_question_list': latest_question_list,
	}
	return render(request, 'polls/index.html', context)
	
	
def detail(request, question_id):
	question = get_object_or_404(Question, pk = question_id) # pk : Primary Key
	context = {
		'question': question,
	}
	return render(request, 'polls/detail.html', context)
	
def results(request, question_id):
	question = get_object_or_404(Question, pk = question_id)
	context = {
		'question': question
	}
	return render(request, 'polls/results.html', context)

def vote(request, question_id):
	question = get_object_or_404(Question, pk = question_id)
	try:
		selected_choice = question.choice_set.get(pk = request.POST['choice'])
	except (KeyError, Choice.DoesNotExist):
		context = {
			'question': question,
			'error_message': "you didn't select a choice.",
		}
		return render(request, 'polls/detail.html', context)
	else:
		selected_choice.votes += 1
		selected_choice.save()
		return HttpResponseRedirect(reverse('polls:results', args = (question.id,)))
