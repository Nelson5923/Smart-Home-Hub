import json
import os
import datetime
import random
import requests
from django.shortcuts import render
from django.shortcuts import redirect
from SmartHomeModel.form import ControlForm
from django.conf import settings
from django.contrib import messages


# Create your views here.

def putThingSpeak(address):

    r = requests.post(address)

    return r

def getThingSpeak(address):

    r = requests.get(address)

    return r.json()

def ControlDevice(request):

    if request.method == 'POST':

        form = ControlForm(request.POST)

        if form.is_valid():

                auto_control = form.cleaned_data.get('auto_control')
                motor_speed = form.cleaned_data.get('motor_speed')
                door_trigger = form.cleaned_data.get('door_trigger')
                led_trigger = form.cleaned_data.get('led_trigger')
                music_trigger = form.cleaned_data.get('music_trigger')

                putThingSpeak("https://api.thingspeak.com/update?api_key=EW7G6EOHQELFAUTF"
                              + "&field1=" + str(motor_speed)
                              + "&field2=" + str(door_trigger)
                              + "&field3=" + str(led_trigger)
                              + "&field4=" + str(music_trigger)
                              + "&field5=" + str(auto_control)
                              )

                messages.success(request, 'Success.')
                return render(request, 'form.html', {'form': form})

        else:

            messages.error(request, 'Fail.')

    else:

        form = ControlForm()

    return render(request, 'form.html', {'form': form})

def DisplaySensor(request):

    SENSOR_VAL_FLAG_GET_ADDRESS = "https://api.thingspeak.com/channels/754991/feeds/last.json?api_key=P1XW47ZYFSB9MRN0"
    sensorVal = getThingSpeak(SENSOR_VAL_FLAG_GET_ADDRESS)
    return render(request, 'status.html', {'sensorVal': sensorVal})





