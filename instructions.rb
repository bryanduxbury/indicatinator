scheme = ARGV.shift.split("")

for i in 0...(scheme.size)
  puts "#{i+1} => #{scheme[i].to_i+1}"
end