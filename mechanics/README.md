# Mechanics

The main structure of Transportino has been made with Fusion360.

The mechanical part has required me some time to not only make minimal functional unit but also to make it printable on my Ender 3 with BL Touch (They can be found on "print_files" folder).

It is essentially made of 3 main parts:
- Back part which contains the **motors** and the **battery**.
- Front part which contains a **raspberry pi** (3B+ in my case but you could use a 4) and the [**main motherboard**](https://github.com/Transportino/transportino/tree/main/electronics)
- Top part which contains the [**Lidar**](https://www.aliexpress.com/item/4001253880158.html?spm=a2g0o.order_list.0.0.21ef1802iWpH9n) and the **container** with a bowl-like shape.

> Those parts have been splitted further to make it printable within the max sizes of my 3d printer, 
so there are some connectors that are not really good right now but will be improved later (*My current main objective is to make the robot functional*).

Structurally It is three wheeled robot with two motors and one caster wheel.

Another important topic is choosing the right motors for my needs.

I decided to go with this two motors from [AliExpress](https://www.aliexpress.com/item/4001339371886.html?spm=a2g0o.order_list.0.0.21ef1802iWpH9n).

Considering that each of my motors have a torque of 6.5 kg • cm (A total of 13 kg • cm torque).
Transportino could theoretically handle up to 2.8 kg (Considering that Transportino weight is around 1 kg).

