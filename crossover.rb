# scheme = [5, 4, 1, 0, 3, 2]
require "rubygems"
require "ruby-debug"
schemes = []

def populate_schemes(alphabet, so_far, results, depth=0)
  if alphabet.empty?
    results << so_far
    return
  end
  for a in alphabet
    # this heuristic allows us to be sure we're never generating a pass-through
    # transposition instruction, since that would basically be the same as 
    # ignoring that pin forever.
    next if a == depth
    populate_schemes(alphabet - [a], so_far.dup << a, results, depth+1)
  end
end

results = []
populate_schemes((0..9).to_a, [], schemes)

puts "generated #{schemes.size} schemes"

# # eliminate all shifted isotopes
# for scheme in schemes
#   while scheme.first != 1
#     scheme << scheme.shift
#   end
# end

# puts "eliminating rotated isotopes yields #{schemes.uniq.size} schemes"
# exit
# puts results.size

# for i in 0..5
#   for j in 0..5
#     next if j == i
#     for k in 0..5
#       next if [i, j].include?(k)
#       for l in 0..5
#         next if [i, j, k].include?(l)
#         for m in 0..5
#           next if [i, j, k, l].include?(m)
#           for n in 0..5
#             next if [i, j, k, l, m].include?(n)
#             schemes << [i, j, k, l, m, n]
#           end
#         end
#       end
#     end
#   end
# end

# puts schemes.map{|x| x.inspect}.sort.join("\n")

def strip_prime(s)
  s.gsub("'", "")
end

def terminating_condition(scheme, occ, nxt)
  if occ.include?(nxt) 
    # puts "#{scheme}: after #{occ.size} steps, repeats on #{nxt}"
    return true
  end
  
  if occ.select{|x| (x[0] == nxt[0] && x[1] == nxt[1]) || (x[0] == nxt[1] && x[1] == nxt[0])}.size > 0
    return true;
  end
  
  nxt_isotope = nxt.dup
  nxt_isotope[0], nxt_isotope[1], = nxt_isotope[1], nxt_isotope[0]
  if occ.include?(nxt_isotope) 
    # puts "#{scheme}: after #{occ.size} steps, repeats on primary isotope of #{nxt}"
    return true
  end
  
  if strip_prime(nxt[0]) == strip_prime(nxt[1])
    # puts "#{scheme}: after #{occ.size} steps, original and prime pin co-occur on #{nxt}"
    return true
  end
  
  if occ.size > 25
    # puts "#{scheme}: after #{occ.size} steps, we've got no end in sight. cool??"
    return true
  end
  
  return false
end

def transform(v, scheme)
  vprime = []
  for s in scheme
    vprime << v[s]
  end
  vprime
end

max_length_scheme = 0
best_schemes = []

for scheme in schemes
  occ = [["0", "1", "2", "3", "4", "0'", "1'", "2'", "3'", "4'"]]

  while true
    cur = occ.last
    nxt = transform(cur, scheme)
    # puts "#{cur} => #{nxt}"
    if terminating_condition(scheme, occ, nxt)
      if occ.size > max_length_scheme
        best_schemes = []
        max_length_scheme = occ.size
      end
      if occ.size == max_length_scheme
        best_schemes << scheme
      end
      break;
    end
    occ << nxt
  end
end

puts "found #{best_schemes.size} schemes with a max length of #{max_length_scheme}"

schemes_with_inversions = []
min_inversions = 1000000

for scheme in best_schemes
  inversions = 0
  scheme.each_with_index do |v, i|
    next if i == 0
    if scheme[i] < scheme[i-1] 
      inversions += 1
    end
  end
  min_inversions = inversions if inversions < min_inversions
  # puts "#{scheme} features #{inversions} inversions"
  schemes_with_inversions << [scheme, inversions]
end

puts schemes_with_inversions.select{|x| x[1] == min_inversions}.map{|x| x[0]}.sort.map{|x| x.join("")}.join("\n")
