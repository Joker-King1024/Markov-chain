from random import choice
import matplotlib.pyplot as plt
class RandomWalk():
    def __init__(self,num_points=5000):
        self.num_points=num_points

        self.x_values=[0]
        self.y_values=[0]

    def fill_walk(self):
        while len(self.x_values)<self.num_points:
            x_direction=choice([1,-1])
            x_distance=choice([0,1,2,3,4])
            x_step=x_direction*x_distance

            y_direction=choice([1,-1])
            y_distance=choice([0,1,2,3,4])
            y_step=y_direction*y_distance

            next_x=self.x_values[-1]+x_step
            next_y=self.y_values[-1]+y_step
#            print(x_direction)
#            print(x_distance)
#            print(x_step)
#            print(next_x)

            self.x_values.append(next_x)
            self.y_values.append(next_y)
#            print(self.x_values)



def main():
    a = RandomWalk()
    a.fill_walk()
    plt.plot(a.x_values,a.y_values)
    plt.show()


if __name__ == "__main__":
    main()

	
