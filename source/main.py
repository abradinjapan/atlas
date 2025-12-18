import pygame
import threading

fps = 60



# run menu
def run_menu(window_dimensions):
    # open window
    screen = pygame.display.set_mode(window_dimensions, (pygame.RESIZABLE | pygame.NOFRAME))
    pygame.display.set_caption("Atlas Menu")

    # setup clock
    clock = pygame.time.Clock()

    # setup menu settings
    display_window = True

    # setup joysticks
    joysticks = {}

    # menu loop
    while display_window:
        # check for closing window
        for event in pygame.event.get():
            # check for quitting menu
            if event.type == pygame.JOYBUTTONDOWN:
                # if menu button is presed
                if event.button == 8:
                    # close menu
                    display_window = False
            # check for contoller added
            if event.type == pygame.JOYDEVICEADDED:
                joy = pygame.joystick.Joystick(event.device_index)
                joysticks[joy.get_instance_id()] = joy
            # check for controller removed
            if event.type == pygame.JOYDEVICEREMOVED:
                del joysticks[event.instance_id]

        # blank window
        screen.fill((0, 0, 255))

        # display frame
        pygame.display.flip()

        # ensure framerate does not excede maximum
        clock.tick(fps)

    return

# main
def main():
    # say activation
    print("Hello Atlas!")

    # run pygame
    pygame.init()

    # menu open / close loop
    #while True:
    # run menu
    run_menu((800, 600))

    # exit
    pygame.quit()
    return

# run atlas
main()
