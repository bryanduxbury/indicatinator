

def transform(v, scheme)
  vprime = []
  for s in scheme
    vprime << v[s]
  end
  vprime
end

input, scheme = ARGV.shift, ARGV.shift
input = input.split(",")
scheme = scheme.split(",").map {|x| x.to_i}

latest = input.dup
while true
  puts latest[0..1].join(",")
  latest = transform(latest, scheme)
  # puts latest[0..1].join(",")
  break if latest == input
end
  
  
