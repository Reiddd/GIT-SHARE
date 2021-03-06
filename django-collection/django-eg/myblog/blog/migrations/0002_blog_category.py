# Generated by Django 2.0.2 on 2018-02-16 13:26

import blog.models
from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('blog', '0001_initial'),
    ]

    operations = [
        migrations.AddField(
            model_name='blog',
            name='category',
            field=models.CharField(choices=[('c++', 'C++'), ('python', 'Python'), ('sql', 'SQL'), ('web', 'HTML/CSS/Bootstrap'), ('qt', 'Qt/PyQt5'), ('git', 'GIT'), ('note', 'notes')], default=blog.models.Blog.category_default, max_length=15),
        ),
    ]
