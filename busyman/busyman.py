
if __name__ == "__main__":
    num_tests = int(input())

    for _ in range(num_tests):
        n = int(input())
        activities = []

        for _ in range(n):
            s = input()
            activity = tuple(map(int, s.split()))
            activities.append(activity)

        sorted_activities = sorted(activities, key = lambda x: x[1])
        solution = []
        current_time = -1
        
        for activity in sorted_activities:
            if activity[0] >= current_time:
                solution.append(activity)
                current_time = activity[1]
        
        print(len(solution))


