.. Software for the Viking watch:

The Viking Watch
##################

Overview
********

This is a work in progress

Building and Running
********************

Build and flash the sample as follows, changing ``nrf52840dk_nrf52840`` for
your board:

.. zephyr-app-commands::
   :zephyr-app: samples/drivers/uart/echo_bot
   :board: nrf52840dk_nrf52840
   :goals: build flash
   :compact:

Sample Output
=============

.. code-block:: console

    Hello! I\'m your echo bot.
    Tell me something and press enter:
    # Type e.g. "Hi there!" and hit enter!
    Echo: Hi there!
