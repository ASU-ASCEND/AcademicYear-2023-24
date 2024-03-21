# Status Codes
ANY SOLID LEDS --> BOARD HAS FROZEN

(No Pins means less than 4 devices were found - indicates that a large chuck of the sensors did not work)

## External LED
| Status                | Code                                              |
|--------               |------                                             |
|ALL GOOD               |Long Blink Short Off                               | 
|Power Distruption      | Blink w/ main                                     |
|No Pins / No File      | Long Blink Long Off                               |
|Error Opening SD Card  | Slow even blink (toggles every 600 ms with blue)  |

## Internal LED
| Status    | Code             |
|--------   |------            |
|ALL GOOD   | Blink w/ main    |

## Color LED (Built-In)
| Status        | Code  |
|--------       |------ |
| No SD Card    | blue  |
| No File       | red   |
| No Pins       | green |


