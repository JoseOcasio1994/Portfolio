using backend_demo.Models;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using Microsoft.IdentityModel.Tokens;
using System.IdentityModel.Tokens.Jwt;
using System.Security.Claims;
using System.Text;

namespace backend_demo.Controllers;

[Route("api/[controller]")]
[ApiController]
public class UserController(IConfiguration configuration, UserContext context) : ControllerBase
{
    private readonly UserContext _context = context;
    private readonly IConfiguration _config = configuration;

    [AllowAnonymous]
    [HttpPost("Login")]
    public async Task<ActionResult<LoginResponseDTO>> Login(LoginRequest loginRequestModel)
    {
        var result = await LoginUser(loginRequestModel);

        if (!result.Success)
        {
            return BadRequest(result.Message);
        }

        var cookieOptions = new CookieOptions
        {
            HttpOnly = true,
            Secure = true, // Use true in production
            SameSite = SameSiteMode.Strict,
            Expires = DateTime.UtcNow.AddHours(1)
        };

        Response.Cookies.Append("token", result.Token, cookieOptions);
        Response.Headers.Authorization = "Bearer " + result.Token;

        return Ok(result);
    }

    [AllowAnonymous]
    [HttpPost("Register")]
    public async Task<ActionResult<RegisterResponse>> Register(RegisterRequest dto)
    {
        User user = new(dto);
        String salt = BCrypt.Net.BCrypt.GenerateSalt(4);
        user.Password = BCrypt.Net.BCrypt.HashPassword(user.Password, salt);

        _context.User.Add(user);
        await _context.SaveChangesAsync();

        RegisterResponse resp = new(user);
        return CreatedAtAction(nameof(Login), new { id = resp.Id }, resp);
    }

    private async Task<LoginResponseDTO> LoginUser(LoginRequest loginRequestModel)
    {
        var getUser = await FindUserByUserName(loginRequestModel.UserName);
        if (getUser == null)
            return new LoginResponseDTO(false, "User Not Found", null);

        bool checkPassword = BCrypt.Net.BCrypt.Verify(loginRequestModel.Password, getUser.Password);
        if (checkPassword)
            return new LoginResponseDTO(true, "Login Successfully", GeneretateJWT(getUser));
        else
            return new LoginResponseDTO(false, "Invalid Password", null);
    }

    private string GeneretateJWT(User user)
    {
        var securityKey = new SymmetricSecurityKey(Encoding.UTF8.GetBytes(_config["Jwt:SecretKey"]!));
        var credentials = new SigningCredentials(securityKey, SecurityAlgorithms.HmacSha256);
        
        var userClaims = new[]
        {
            new Claim(ClaimTypes.NameIdentifier, user.Id.ToString()),
            new Claim(ClaimTypes.Name, user.Name!),
            new Claim(ClaimTypes.Email, user.Email!),
            new Claim(ClaimTypes.UserData, user.UserName!),
            new Claim(ClaimTypes.Role, user.Role!)
        };

        var token = new JwtSecurityToken(
            issuer: _config["Jwt:Issuer"],
            audience: _config["Jwt:Audience"],
            claims: userClaims,
            expires: DateTime.Now.AddDays(5),
            signingCredentials: credentials
            );

        Console.WriteLine(token);
        return new JwtSecurityTokenHandler().WriteToken(token);
    }

    private async Task<User?> FindUserByUserName(String user)
    {
        var resp = await _context.User.FirstOrDefaultAsync(u => u.UserName == user);
        return resp;
    }

}
