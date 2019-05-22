from django import forms
from django.forms import ModelChoiceField

class ControlForm(forms.Form):
    auto_control = forms.CharField(label="AutoControl: ",max_length=1)
    motor_speed = forms.CharField(label="MotorSpeed: ", max_length=2540)
    door_trigger = forms.CharField(label="DoorLockTrigger: ", max_length=1)
    led_trigger = forms.CharField(label="LEDTrigger: ", max_length=1)
    music_trigger = forms.CharField(label="MusicTrigger: ", max_length=1)
